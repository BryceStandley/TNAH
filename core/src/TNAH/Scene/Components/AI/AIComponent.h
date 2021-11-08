/*****************************************************************//**
 * @file   AIComponent.h
 * @brief  Holds the AI information
 * 
 * @author chris
 * @date   November 2021
 *********************************************************************/
#pragma once
# define PI           3.14159265358979323846
#include "AStar.h"
#include "Character.h"
#include "TNAH/Core/Timestep.h"

namespace tnah
{
    inline double randFloat()
    {
        return ((rand()) / (RAND_MAX + 1.0));
    }

    inline double randomClamped()
    {
        return randFloat() - randFloat();
    }
    
    class AIComponent
    {
    public:
        AIComponent()
        {
            m_Velocity = glm::vec3(1, 0 , 1);
            currentlyWandering = true;
        }

        ~AIComponent()
        {
            
        }
        /**
         *
         * @fn GetTargetPosition
         * @brief 
         * 
         * @return 
         * @author chris
         */
        const glm::vec3& GetTargetPosition() const;
        /**
         *
         * @fn SetTargetPosition
         * @brief 
         * 
         * @param targetPosition
         * @author chris
         */
        void SetTargetPosition(const glm::vec3& targetPosition);
        /**
         *
         * @fn TargetCutoffDistance
         * @brief 
         * 
         * @return 
         * @author chris
         */
        float TargetCutoffDistance() const;
        /**
         *
         * @fn SetTargetCutoffDistance
         * @brief 
         * 
         * @param targetCutoffDistance
         * @author chris
         */
        void SetTargetCutoffDistance(float targetCutoffDistance);
        
        /**
         *
         * @fn MovementSpeed
         * @brief 
         * 
         * @return 
         * @author chris
         */
        float MovementSpeed() const;
        /**
         *
         * @fn SetMovementSpeed
         * @brief 
         * 
         * @param movementSpeed
         * @author chris
         */
        void SetMovementSpeed(float movementSpeed);
        /**
         *
         * @fn MovementAllowed
         * @brief 
         * 
         * @return 
         * @author chris
         */
        bool MovementAllowed() const;
        /**
         *
         * @fn SetMovementAllowed
         * @brief 
         * 
         * @param movementAllowed
         * @author chris
         */
        void SetMovementAllowed(bool movementAllowed);
        /**
         *
         * @fn SetVelocity
         * @brief 
         * 
         * @param vel
         * @author chris
         */
        void SetVelocity(const glm::vec3 vel) { m_Velocity = vel; }
        /**
         *
         * @fn SetWander
         * @brief 
         * 
         * @param w
         * @author chris
         */
        void SetWander(bool w) {currentlyWandering = w;}
        /**
         *
         * @fn GetWander
         * @brief 
         * 
         * @return 
         * @author chris
         */
        bool GetWander() const {return currentlyWandering;}
        /**
         *
         * @fn OnUpdate
         * @brief Updates the ai compoennt sorting out wanders ect
         * 
         * @param deltaTime
         * @param trans
         * @author chris
         */
        void OnUpdate(Timestep deltaTime, TransformComponent &trans);

        /**
         *
         * @fn GetPositions
         * @brief 
         * 
         * @return 
         * @author chris
         */
        std::deque<Node> GetPositions() {return currentPath;}
    private:
        /**
         *
         * @fn moveTo
         * @brief Moves to the given location
         * 
         * @param curPos
         * @param targetPos
         * @param curVelocity
         * @param time
         * @param rot
         * @return 
         * @author chris
         */
        bool moveTo(glm::vec3& curPos, const glm::vec3& targetPos, glm::vec3& curVelocity, float time, glm::vec3& rot);

    private:
        /** Target position of the object */
        glm::vec3 m_TargetPosition = {};
        /** cuttoff distance */
        float m_TargetCutoffDistance = 1.0f;
        /**  Movement speed */
        float m_MovementSpeed = 1.0f;
        /**  if it is allowed to move */
        bool m_MovementAllowed = true;
        /** The current velocity */
        glm::vec3 m_Velocity = {};
        /**  if it is current wandering */
        bool currentlyWandering;
        //AStar stuff
        /**  The current position*/
        Node currentPosition;
        /**  The current destination*/
        Node destination;
        /**  The current path*/
        std::deque<Node> currentPath = {};

        inline static std::string s_SearchString = "AiCharacter Component";
        /** @brief	Type identifiers for the component */
        inline static ComponentTypes s_Types = {
            {ComponentVariations::AiCharacter},
{{ComponentCategory::Physics}}
        };
        friend class EditorUI;
    };

    inline const glm::vec3& AIComponent::GetTargetPosition() const
    {
        return m_TargetPosition;
    }

    inline void AIComponent::SetTargetPosition(const glm::vec3& targetPosition)
    {
        m_TargetPosition = targetPosition;
    }

    inline float AIComponent::TargetCutoffDistance() const
    {
        return m_TargetCutoffDistance;
    }

    inline void AIComponent::SetTargetCutoffDistance(float targetCutoffDistance)
    {
        m_TargetCutoffDistance = targetCutoffDistance;
    }

    inline float AIComponent::MovementSpeed() const
    {
        return m_MovementSpeed;
    }

    inline void AIComponent::SetMovementSpeed(float movementSpeed)
    {
        m_MovementSpeed = movementSpeed;
    }

    inline bool AIComponent::MovementAllowed() const
    {
        return m_MovementAllowed;
    }

    inline void AIComponent::SetMovementAllowed(bool movementAllowed)
    {
        m_MovementAllowed = movementAllowed;
    }
}
