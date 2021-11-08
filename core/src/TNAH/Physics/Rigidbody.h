#pragma once

#include "PhysicsStructures.h"
#include "Collider.h"
#include "TNAH/Scene/Components/Components.h"

namespace tnah::Physics {

    /**
     * @class RigidBody
     *
     * @brief A class that defines all rigidbody physics body properties.
     *
     * @author Bryce Standley
     * @date 20/10/2021
     *
     */
    class RigidBody : public RefCounted
    {
    public:

        /**
         * @brief Construct a new Rigid Body object
         * @author Bryce Standley
         * @date 06-11-2021
         */
        RigidBody();

        /**
         * @brief Construct a new Rigid Body object
         * @author Bryce Standley
         * @date 06-11-2021
         */
        RigidBody(TransformComponent& transform, BodyMass mass, BodyType type = BodyType::Dynamic);

        /**
         * @brief Creates a Ref to a RigidBody object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return Ref<RigidBody> 
         */
        static Ref<RigidBody> Create(TransformComponent& transform, BodyMass mass, BodyType type = BodyType::Dynamic);

        /**
         * @brief Updates the body
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void OnUpdate(TransformComponent& transform);

        /**
         * @brief Get the Body Mass object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return BodyMass 
         */
        BodyMass GetBodyMass() const { return m_BodyMass; }

        /**
         * @brief Adds force to the body (Linear)
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void AddForce(const glm::vec3& force);

        /**
         * @brief Adds torque to the body (Angular)
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void AddTorque(const glm::vec3& torque);

        /**
         * @brief Set the Collision Body object
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void SetCollisionBody(rp3d::CollisionBody* collisionBody) { m_CollisionBody = collisionBody; }

        /**
         * @brief Get the Collision Body object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return rp3d::CollisionBody* 
         */
        rp3d::CollisionBody* GetCollisionBody() const { return m_CollisionBody; }

        /**
         * @brief Adds a collider to the body
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void AddCollider(Ref<Collider> collider);

        /**
         * @brief Get the Colliders objects
         * @author Bryce Standley
         * @date 06-11-2021
         * @return std::unordered_map<uint32_t, Ref<Collider>> 
         */
    	std::unordered_map<uint32_t, Ref<Collider>> GetColliders() { return m_Colliders; }

        /**
         * @brief Checks if colliders have been attached to the body
         * @author Bryce Standley
         * @date 06-11-2021
         * @return true 
         * @return false 
         */
    	bool HasColliders() const { return m_TotalColliders > 0 ? true : false; }
        
        /**
         * @fn tnah::Physics::RigidBody::UpdateBodyProperties()
         * 
         * @brief Updates and recalculates the Local properties of the RigidBody based on its colliders attached.
         *	This overrides any values set. To modify the properties of the body,
         *	address the tnah::Physics::Collider objects directly with RigidBody::GetColliders()
         *
         * @author Bryce Standley
         * @date Monday, 25 October 2021
         * 
         */
        void UpdateBodyProperties();

        /**
         * @brief Gets the ID of the body
         * @author Bryce Standley
         * @date 06-11-2021
         * @return uint32_t 
         */
        uint32_t GetID() const { return m_ID; }

        /**
         * @brief Set the Type object
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void SetType(const BodyType& type) { m_BodyType = type; }

        /**
         * @brief Get the Type object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return BodyType 
         */
        BodyType GetType() const { return m_BodyType; }

        /**
         * @brief Get the Inertia Tensor object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return InertiaTensor 
         */
        InertiaTensor GetInertiaTensor() const { return m_InertiaTensor; }

        /**
         * @brief Recalculates the inertia tensor in world space
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void RecalculateWorldInertiaTensor();
    	
        /**
         * @brief Get the Linear Velocity object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return LinearVelocity 
         */
        LinearVelocity GetLinearVelocity() const { return m_LinearVelocity; }

        /**
         * @brief Get the Angular Velocity object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return AngularVelocity 
         */
        AngularVelocity GetAngularVelocity() const { return m_AngularVelocity; }

        /**
         * @brief Get the Velocities objects
         * @author Bryce Standley
         * @date 06-11-2021
         * @return std::pair<LinearVelocity, AngularVelocity> 
         */
        std::pair<LinearVelocity, AngularVelocity> GetVelocities() { return {m_LinearVelocity, m_AngularVelocity}; }

        /**
         * @brief Set the Linear Rotational Lock Factor object
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void SetLinearRotationalLockFactor(const glm::ivec3& lock) { m_LinearRotationLock = lock; }

        /**
         * @brief Set the Angular Rotational Lock Factor object
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void SetAngularRotationalLockFactor(const glm::ivec3& lock) { m_AngularRotationLock = lock; }

        /**
         * @brief Get the Linear Rotational Lock Factor object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return glm::vec3& 
         */
        glm::vec3& GetLinearRotationalLockFactor() { return m_LinearRotationLock; }

        /**
         * @brief Get the Angular Rotational Lock Factor object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return glm::vec3& 
         */
        glm::vec3& GetAngularRotationalLockFactor() { return m_AngularRotationLock; }

        /**
         * @brief Applies a collision Impulse to the body (Unused)
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void ApplyCollisionImpulse(const glm::vec3& linearVelocity, const glm::vec3& angularVelocity);

        /**
         * @brief Resets the velocity, position and orientation values of the body
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void ResetValues();

        /**
         * @brief Reference to ignore gravity flag. Used to toggle between ignoring or not ignoring gravity
         * @author Bryce Standley
         * @date 06-11-2021
         * @return true 
         * @return false 
         */
        bool& IgnoreGravity() { return m_IgnoreGravity; }

        /**
         * @brief Checks if the body is sleeping
         * @author Bryce Standley
         * @date 06-11-2021
         * @return true 
         * @return false 
         */
        bool IsSleeping() const { return m_IsSleeping; }

        /**
         * @brief Wakes up the body from sleep
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void Awake() { m_IsSleeping = false; }

        /**
         * @brief Sets a body to sleep
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void Sleep();

        /**
         * @brief Set the Linear Dampening object, clamping between 0 and 1
         * @author Bryce Standley
         * @date 06-11-2021
         */
    	void SetLinearDampening(float value) {m_LinearDampening.Dampening = glm::clamp(value, 0.0f, 1.0f);}

        /**
         * @brief Set the Angular Dampening object, clamping between 0 and 1
         * @author Bryce Standley
         * @date 06-11-2021
         */
    	void SetAngularDampening(float value) {m_AngularDampening.Dampening = glm::clamp(value, 0.0f, 1.0f);}

        /**
         * @brief Calculates the local inertia tensor
         * @author Bryce Standley
         * @date 06-11-2021
         * @return glm::vec3 
         */
        glm::vec3 CalculateLocalInertiaTensor();


    private:

        /**
         * @brief Calculates the centre of mass of the body
         * @author Bryce Standley
         * @date 06-11-2021
         * @return glm::vec3 
         */
    	glm::vec3 CalculateCentreOfMass();

        /**
         * @brief Sets the ID of the body 
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void SetID(const uint32_t id) { m_ID = id; }
        
    
    private:

        /**
         * @var m_BodyType
         *
         * @brief The type of the Rigidbody. Either Dynamic or static. 
         */
        BodyType m_BodyType;

        /**
        * @var m_BodyMass
        *
        * @brief The BodyMass of the Rigidbody. This is the combined total for the whole Rigidbody with all of its Colliders.
        */
        BodyMass m_BodyMass;

        /**
        * @var m_LinearVelocity
        *
        * @brief The current LinearVelocity of the Rigidbody.
        */
        LinearVelocity m_LinearVelocity;

        /**
        * @var m_AngularVelocity
        *
        * @brief The current AngularVelocity of the Rigidbody.
        */
        AngularVelocity m_AngularVelocity;

        /**
        * @var m_ConstrainedLinearVelocity
        *
        * @brief The current Constrained LinearVelocity of the Rigidbody.
        */
        LinearVelocity m_ConstrainedLinearVelocity;

        /**
        * @var m_ConstrainedAngularVelocity
        *
        * @brief The current Constrained AngularVelocity of the Rigidbody.
        */
        AngularVelocity m_ConstrainedAngularVelocity;

        /**
        * @var m_Force
        *
        * @brief Current forces applied to the Rigidbody. These are used and zeroed out every PhysicsSystem::OnUpdate().
        */
        Force m_Force;

        /**
        * @var m_Torque
        *
        * @brief Current torques applied to the Rigidbody. These are used and zeroed out every PhysicsSystem::OnUpdate().
        */
        Torque m_Torque;

        /**
        * @var m_LinearDampening
        *
        * @brief The LinearDampening of the Rigidbody. Values of 0 disable dampening and values of 1 enable full dampening.
        */
        LinearDampening m_LinearDampening;

        /**
        * @var m_AngularDampening
        *
        * @brief The AngularDampening of the Rigidbody. Values of 0 disable dampening and values of 1 enable full dampening.
        */
        AngularDampening m_AngularDampening;

        /**
        * @var m_InertiaTensor
        *
        * @brief The InertiaTensor of the Rigidbody with both world and local space data.
        */
        InertiaTensor m_InertiaTensor;
        
        /**
        * @var m_Colliders
        *
        * @brief A vector of all colliders on the Rigidbody
        */
        std::unordered_map<uint32_t, Ref<Collider>> m_Colliders;

        /**
         * @var m_TotalColliders
         * @brief Total colliders attached to the body
         * @author Bryce Standley
         * @date 06-11-2021
         */
    	uint32_t m_TotalColliders = 0;

    	/**
    	 * @var m_ID
    	 * 
    	 * @brief The global ID of the RigidBody.
    	 */
        uint32_t m_ID = 0;

        /**
         * @var m_LinearRotationLock
         *
         * @brief Rotational lock factor for linear velocities. 1 is enabled, 0 is disabled per axis.
         */
        glm::vec3 m_LinearRotationLock = {1,1,1};

        /**
        * @var m_AngularRotationLock
        *
        * @brief Rotational lock factor for angular velocities. 1 is enabled, 0 is disabled per axis.
        */
        glm::vec3 m_AngularRotationLock = {1,1,1};

        /**
         * @var m_Position
         * @brief World position of the body
         * @author Bryce Standley
         * @date 06-11-2021
         */
    	glm::vec3 m_Position = {0,0,0};
    	
        /**
         * @var m_Orientation
         * @brief World orientation of the body
         * @author Bryce Standley
         * @date 06-11-2021
         */
        glm::quat m_Orientation = {0,0,0,0};

    	/**
    	 * @var m_IsSleeping
    	 *
    	 * @brief A flag to note if the RigidBody is currently sleeping thus not being simulated.
    	 */
        bool m_IsSleeping = false;

        /**
         * @var m_SleepVelocityThreshold
         * @brief Threshold to sleep based on velocity
         * @author Bryce Standley
         * @date 06-11-2021
         */
    	float m_SleepVelocityThreshold = 0.2f;

        /**
         * @var m_SleepTimeThreshold
         * @brief Threshold to sleep based on time
         * @author Bryce Standley
         * @date 06-11-2021
         */
    	float m_SleepTimeThreshold = 1.0f;

        /**
         * @var m_SleepTimeAccumulator
         * @brief Accumulator of time when the body reached the threshold velocity to sleep
         * @author Bryce Standley
         * @date 06-11-2021
         */
    	float m_SleepTimeAccumulator = 0.0f;

    	/**
    	* @var m_IgnoreGravity
    	*
    	* @brief A flag to note if the RigidBody should ignore gravity within the world.
    	*/
        bool m_IgnoreGravity = false;

        /**
    	* @var m_CollisionBody
    	*
    	* @brief The Reactphysics3d Collision body used by the Rigidbody to interact and move within the PhysicsWorld.
    	*/
    	rp3d::CollisionBody* m_CollisionBody = nullptr;
        

        friend class PhysicsEngine;
        friend class EditorUI;
        friend class Serializer;
    };
}
