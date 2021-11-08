#include <tnahpch.h>
#include "PhysicsComponents.h"
#include "TNAH/Scene/GameObject.h"

namespace tnah
{

#pragma region Rigidbody


    RigidBodyComponent::RigidBodyComponent()
    {}

    RigidBodyComponent::RigidBodyComponent(GameObject& gameObject, const Physics::BodyType& type)
    {
        if(Physics::PhysicsEngine::IsActive())
        {
            Body = Physics::PhysicsEngine::CreateRigidbody(gameObject);
            Body->SetType(type);
            Body->GetCollisionBody()->setUserData(&gameObject);
        }
    }

    void RigidBodyComponent::OnUpdate(TransformComponent& transform)
    {
        Body->OnUpdate(transform);
    }
    

    void RigidBodyComponent::ApplyForce(const glm::vec3& direction, const glm::vec3& force)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            Body->AddForce(direction * force);
        }
    }

    void RigidBodyComponent::ApplyTorque(const glm::vec3& direction,const glm::vec3& torque)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            Body->AddForce(direction * torque);
        }
    }

    Ref<Physics::Collider> RigidBodyComponent::AddCollider(const glm::vec3& boxSize)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            return Physics::PhysicsEngine::CreateBoxCollider(Body, boxSize);
        }
        return nullptr;
    }

    Ref<Physics::Collider> RigidBodyComponent::AddCollider(const glm::vec3& boxSize, const glm::vec3& localPosition,
    const glm::quat& localOrientation, const float& density, const float& volume)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            auto col = Physics::PhysicsEngine::CreateBoxCollider(Body, boxSize);
            col->SetPosition(localPosition);
            col->SetOrientation(localOrientation);
            col->SetDensity(density);
            col->SetVolume(volume);
            return col;
        }
        return nullptr;
    }

    Ref<Physics::Collider> RigidBodyComponent::AddCollider(const float& sphereRadius)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            return Physics::PhysicsEngine::CreateSphereCollider(Body, sphereRadius);
        }
        return nullptr;
    }

    Ref<Physics::Collider> RigidBodyComponent::AddCollider(const float& sphereRadius, const glm::vec3& localPosition,
    const glm::quat& localOrientation, const float& density, const float& volume)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            auto col = Physics::PhysicsEngine::CreateSphereCollider(Body, sphereRadius);
            col->SetPosition(localPosition);
            col->SetOrientation(localOrientation);
            col->SetDensity(density);
            col->SetVolume(volume);
            return col;
        }
        return nullptr;
    }

    Ref<Physics::Collider> RigidBodyComponent::AddCollider(const float& capsuleRadius, const float& capsuleHeight)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            return Physics::PhysicsEngine::CreateCapsuleCollider(Body, capsuleRadius, capsuleHeight);
        }
        return nullptr;
    }

    Ref<Physics::Collider> RigidBodyComponent::AddCollider(const float& capsuleRadius, const float& capsuleHeight,
    const glm::vec3& localPosition, const glm::quat& localOrientation, const float& density, const float& volume)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            auto col = Physics::PhysicsEngine::CreateCapsuleCollider(Body, capsuleRadius, capsuleHeight);
            col->SetPosition(localPosition);
            col->SetOrientation(localOrientation);
            col->SetDensity(density);
            col->SetVolume(volume);
            return col;
        }
        return nullptr;
    }
#pragma endregion
 
}
