#include "tnahpch.h"
#include "AIComponent.h"

namespace tnah {


    void AIComponent::OnUpdate(Timestep deltaTime, TransformComponent &trans)
    {
        currentPosition.position = {static_cast<int>(round(trans.Position.x)), static_cast<int>(round(trans.Position.z))};
        if(currentlyWandering)
        {
            if(!currentPath.empty())
            {
                const auto path = currentPath.front();
                if(!AStar::IsValid(path.position))
                {
                    if(!AStar::IsValid(destination.position))
                    {
                        currentPath.clear();
                    }
                    else
                        currentPath = AStar::Algorithm(currentPosition, destination);
                }
                else if(AStar::Reached(currentPosition.position, path) || moveTo(trans.Position, glm::vec3(path.position.x, trans.Position.y, path.position.y), m_Velocity, deltaTime.GetSeconds(), trans.Rotation))
                {
                    currentPath.pop_front();
                }
            }
            else
            {
                destination = AStar::GenerateRandomPosition(currentPosition.position);
                currentPath = AStar::Algorithm(currentPosition, destination);
            }
        }

        currentPosition.position = {static_cast<int>(round(trans.Position.x)), static_cast<int>(round(trans.Position.z))};
    }

    bool AIComponent::moveTo(glm::vec3& curPos, const glm::vec3& targetPos, glm::vec3& curVelocity, float time, glm::vec3& rot)
    {
        //calc heading from character position to target
        glm::vec3 target = targetPos - curPos;
        target = glm::normalize(target);

        if (target.x == 0 && target.y == 0 && target.z == 0)
            return true;

        //calc new velocity and new character position
        curVelocity = target * glm::length(curVelocity);
        glm::vec3 displacement = curVelocity * time * m_MovementSpeed;
        glm::vec3 vec = curPos + displacement;

        SetVelocity(curVelocity);

        // calculate real target position
        glm::vec3 realTargetPos = targetPos - target;

        // calculate the direction from vec to realTargetPos
        glm::vec3 toRealTarget = realTargetPos - vec;
        //rot = toRealTarget;
        toRealTarget = glm::normalize(toRealTarget);
        if (toRealTarget.x == 0 && toRealTarget.y == 0 && toRealTarget.z == 0)
        {
            curPos = realTargetPos;
            //SetPos(curPos);
            m_TargetPosition = curPos;
            return true;
        }

        //check to see whether vec has gone pass the realTargetPos
        float dp = glm::distance(toRealTarget, target);

        if (dp < 0.0)
        {
            m_TargetPosition = curPos;
            return true;
        }

        curPos = vec;

        //SetPos(curPos);
        m_TargetPosition = curPos;
        return false;
    }

}