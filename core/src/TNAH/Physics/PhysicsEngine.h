#pragma once
#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>

#pragma warning(pop)

#include <entt.hpp>

#include "CollisionDetectionEngine.h"
#include "PhysicsStructures.h"
#include "Rigidbody.h"
#include "TNAH/Physics/PhysicsTimestep.h"
#include "TNAH/Scene/Components/Components.h"
#include "TNAH/Scene/Components/PhysicsComponents.h"
#include "Rigidbody.h"
#include "TNAH/Core/Timestep.h"

#include "TNAH/Scene/Components/PhysicsComponents.h"

namespace tnah {
    class Scene;
    class Renderer;
    class GameObject;
}

/**
 * @namespace tnah::Physics {}
 *
 * @brief Main Physics Sub-namespace
 *
 */
namespace tnah::Physics
{
 
#pragma region PhysicsManager
 
 /**
     * @class	PhysicsManager
     *
     * @brief	Manager for physics that inherits from the RefCounted class. This class is to remain private and contain
     * all ReactPhysics3D world objects. Any control of the PhysicsManager should be done from tnah::PhysicsEngine::PhysicsEngine
     *
     * @author	Chris Logan
     * @date	11/09/2021
     */

    class PhysicsManager : public RefCounted
    {
    public:

        /**
         * @fn	PhysicsManager::PhysicsManager();
         *
         * @brief	Default constructor.
         * This constructor is empty as the object requires the PhysicsEngine::Initialise(rp3d::EventListener* collisionEventListener) to be called 
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */

        PhysicsManager();

        /**
         * @fn	PhysicsManager::~PhysicsManager();
         *
         * @brief	Destructor. Safeguards prevent deletion of empty pointers of
         * PhysicsManager::m_PhysicsWorld and PhysicsManager::m_PhysicsLogger if PhysicsEngine::Initialise(rp3d::EventListener* collisionEventListener)
         * was never called or PhysicsEngine::Initialise(rp3d::EventListener* collisionEventListener) was called and PhysicsEngine::PhysicsLoggerInit() was not.
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */

        ~PhysicsManager();

        /**
         * @brief Get the Gravity object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return glm::vec3& 
         */
        glm::vec3& GetGravity() { return m_Gravity; }

        /**
         * @brief Set the Gravity object
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void SetGravity(const glm::vec3& gravity) { m_Gravity = gravity; }

        /**
         * @brief Set the Gravity State object
         * @author Bryce Standley
         * @date 06-11-2021
         */
        void SetGravityState(const bool& state) { m_GravityEnabled = state; }

        /**
         * @brief Get the Gravity State object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return true 
         * @return false 
         */
        bool& GetGravityState() { return m_GravityEnabled; }

        /**
         * @brief Get the Sleep State object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return true 
         * @return false 
         */
        bool& GetSleepState() { return m_SleepAllowed; }

        /**
         * @brief Get the Collision Detection Engine object
         * @author Bryce Standley
         * @date 06-11-2021
         * @return Ref<CollisionDetectionEngine>& 
         */
        Ref<CollisionDetectionEngine>& GetCollisionDetectionEngine() { return m_CollisionDetectionEngine; }

    private:
        /**
         * @fn	bool PhysicsManager::Initialise(rp3d::EventListener * collisionEventListener);
         *
         * @brief	Initialises this object
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	collisionEventListener	If non-null, the collision event listener.
         *
         * @returns	True if it succeeds, false if it fails.
         */
        bool Initialise(rp3d::EventListener * collisionEventListener);

        /**
         * @fn	void PhysicsManager::OnFixedUpdate(PhysicsTimestep timestep);
         *
         * @brief	Executes the 'fixed update' action
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	timestep	The timestep.
         */
        void OnFixedUpdate(Timestep deltaTime, PhysicsTimestep timestep) const;

        /**
         * @fn	void PhysicsManager::Destroy();
         *
         * @brief	Destroys this object
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */
        void Destroy();

        /**
         * @fn	rp3d::RigidBody* PhysicsManager::CreateRigidBody(const TransformComponent& transform);
         *
         * @brief	Creates rigid body
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	transform	A transform component.
         *
         * @returns	Null if it fails, else the new rigid body.
         */
        rp3d::RigidBody* CreateRigidBody(const TransformComponent& transform) const;

        /**
         * @fn	void PhysicsManager::DestroyRigidBody(rp3d::RigidBody* rigidBody);
         *
         * @brief	Destroys the rigid body described by rigidBody
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	rigidBody	If non-null, the rigid body.
         */
        void DestroyRigidBody(rp3d::CollisionBody* rigidBody) const;

        /**
         * @fn	rp3d::CollisionBody* PhysicsManager::CreateCollisionBody(const TransformComponent& transform);
         *
         * @brief	Creates collision body
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	transform	The transform.
         *
         * @returns	Null if it fails, else the new collision body.
         */
        rp3d::CollisionBody* CreateCollisionBody(const TransformComponent& transform) const;

        /**
         * @fn	void PhysicsManager::DestroyCollisionBody(rp3d::CollisionBody * body);
         *
         * @brief	Destroys the collision body described by body
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	body	If non-null, the body.
         */
        void DestroyCollisionBody(rp3d::CollisionBody * body) const;

        /**
         * @fn	void PhysicsManager::CreateColliderRenderer();
         *
         * @brief	Creates collider renderer
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */
        void CreateColliderRenderer();

   
    
    private:
        /** @brief	The physics common */
        rp3d::PhysicsCommon m_PhysicsCommon;

        /** @brief	Pointer to The physics world */
        rp3d::PhysicsWorld* m_PhysicsWorld = nullptr;

        /** @brief	Pointer to physics logger */
        rp3d::DefaultLogger* m_PhysicsLogger = nullptr;

        /** @brief	True to collider render */
        bool m_ColliderRender = false;

        /** @brief	True if the collider renderer has been initialized */
        bool m_ColliderRendererInit = false;

        Ref<VertexArray> m_LinesVertexArray;
     
        /** @brief	Pointer to the buffer for lines vertex data */
        Ref<VertexBuffer> m_LinesVertexBuffer;

        /** @brief	Pointer to array for triangle vertex data */
        Ref<VertexArray> m_TriangleVertexArray;

        /** @brief	Pointer to Buffer for triangle vertex data */
        Ref<VertexBuffer> m_TriangleVertexBuffer;

        /** @brief	Shader used for the collider renderer */
        Ref<Shader> m_Shader;

        /** @brief	Layout of the collider renderer vertex buffers */
        VertexBufferLayout m_ColliderLayout;

        /**
         * @brief If gravity is enabled or not
         * @author Bryce Standley
         * @date 06-11-2021
         */
        bool m_GravityEnabled = true;

        /**
         * @brief The value of gravity in the world
         * @author Bryce Standley
         * @date 06-11-2021
         */
        glm::vec3 m_Gravity = {0.0f, -9.8f, 0.0f};

        /** @brief	True to active */
        bool m_Active = false;

        /** @brief Used to tell the physics system if the logging should be enabled*/
        bool m_Logging = false;

        /**
         * @brief All RigidBody objects in the world
         * @author Bryce Standley
         * @date 06-11-2021
         */
        std::unordered_map<uint32_t, Ref<RigidBody>> m_Rigidbodies;

        /**
         * @brief Total Rigidbody objects in the world
         * @author Bryce Standley
         * @date 06-11-2021
         */
        uint32_t m_TotalRigidbodies = 0;

        /**
         * @brief All Collider objects in the world
         * @author Bryce Standley
         * @date 06-11-2021
         */
        std::unordered_map<uint32_t, Ref<Collider>> m_Colliders;

        /**
         * @brief Total Collider objects in the world
         * @author Bryce Standley
         * @date 06-11-2021
         */
        uint32_t m_TotalColliders = 0;

        /** @brief a static reference to the active Collision Detection Engine */
        static Ref<CollisionDetectionEngine> m_CollisionDetectionEngine;

        /**
         * @brief Are RigidBody objects allowed to sleep?
         * @author Bryce Standley
         * @date 06-11-2021
         */
        bool m_SleepAllowed = false;

        friend class PhysicsEngine;
};

#pragma endregion PhysicsManager

#pragma region PhysicsEngine
 
    /**
     * @class	PhysicsEngine
     *
     * @brief	A physics class responsible for the engine physics. All actual physics calculations are processed within
     * this class.
     *
     * @author	Bryce Standley
     * @date	12/09/2021
     */
    class PhysicsEngine
    {
    public:

        /**
         * @fn	static Ref<PhysicsManager> PhysicsEngine::GetManager();
         *
         * @brief	Gets a pointer to the PhysicsManager
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The manager.
         */
        static Ref<PhysicsManager> GetManager();

        /**
         * @fn	static bool PhysicsEngine::IsActive();
         *
         * @brief	Query if the physics is active
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	True if active, false if not.
         */
        static bool IsActive();

        /**
         * @fn	static bool PhysicsEngine::Initialise(rp3d::EventListener * collisionEventListener);
         *
         * @brief	Initialises the physics and its logger
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	collisionEventListener	If non-null, the collision event listener.
         *
         * @returns	True if it succeeds, false if it fails.
         */
        static bool Initialise(rp3d::EventListener * collisionEventListener);

        /**
         * @fn	static void PhysicsEngine::OnFixedUpdate(PhysicsTimestep timestep);
         *
         * @brief	Executes the 'fixed update' action
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	timestep	The timestep.
         */
        static void OnFixedUpdate(Timestep deltaTime, PhysicsTimestep timestep, entt::registry& componentRegistry);

        /**
         * @fn	static void PhysicsEngine::OnUpdate(Timestep timestep);
         *
         * @brief	Physics update for any disconnected objects not tied directly to the fixed physics updates.
         *
         * @author	Bryce Standley
         * @date	10/10/2021
         *
         * @param 	timestep	The timestep.
         */
        static void OnUpdate(Timestep timestep);

        /**
         * @fn	static void PhysicsEngine::Destroy();
         *
         * @brief	Destroys this object
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */
        static void Destroy();

        /**
         * @fn	static void PhysicsEngine::DestroyRigidbody(rp3d::RigidBody* body);
         *
         * @brief	Destroys the rigidbody described by body
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	body	If non-null, the body.
         */
        static void DestroyRigidbody(Ref<RigidBody> rigidbody);

        /**
         * @fn	static rp3d::RigidBody* PhysicsEngine::CreateRigidbody(const TransformComponent& transform);
         *
         * @brief	Creates a rigidbody
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	transform	The transform.
         *
         * @returns	Null if it fails, else the new rigidbody.
         */
        static Ref<RigidBody> CreateRigidbody(GameObject& gameObject);

        /**
         * @fn	static void PhysicsEngine::ToggleColliderRendering();
         *
         * @brief	Toggle collider rendering
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */
        static void ToggleColliderRendering();

        /**
         * @fn	static void PhysicsEngine::GetColliderRendererHandle();
         *
         * @brief	Gets the Collider renderer handle
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */
        static bool& GetColliderRendererHandle();

        /**
         * @fn	static TransformComponent PhysicsEngine::GetColliderRendererTransform();
         *
         * @brief	Gets the transform of the renderer
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */
        static TransformComponent GetColliderRendererTransform();

        /**
         * @fn   static Ref<Collider> CreateBoxCollider(Ref<RigidBody> rigidbody, const glm::vec3& halfExtents);
         *
         * @brief	Creates box shape
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	rigidbody	
         * @param 	halfExtents	Extents of the half.
         *
         * @returns	Null if it fails, else the new box shape.
         */
        static Ref<Collider> CreateBoxCollider(Ref<RigidBody> rigidbody, const glm::vec3& halfExtents);

        /**
         * @fn    static Ref<Collider> CreateSphereCollider(Ref<RigidBody> rigidbody, const float& radius);
         *
         * @brief	Creates sphere shape
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	rigidbody	
         * @param 	radius	The radius.
         *
         * @returns	Null if it fails, else the new sphere shape.
         */
        static Ref<Collider> CreateSphereCollider(Ref<RigidBody> rigidbody, const float& radius);

        /**
         * @fn	   static Ref<Collider> CreateCapsuleCollider(Ref<RigidBody> rigidbody, const float& radius, const float& height);
         *
         * @brief	Creates capsule shape
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	rigidbody	
         * @param 	radius	The radius.
         * @param 	height	The height.
         *
         * @returns	Null if it fails, else the new capsule shape.
         */
        static Ref<Collider> CreateCapsuleCollider(Ref<RigidBody> rigidbody, const float& radius, const float& height);
    
    private:

        /**
        * @fn	void PhysicsEngine::EnableLogging();
        *
        * @brief	Enables logging for the physics system
        *
        * @author	Bryce Standley
        * @date	12/09/2021
        *
        */
        static void EnableLogging();

        /**
        * @fn   static bool IsColliderRenderingEnabled();
        *
        * @brief	Checks if collider rendering is enabled
        *
        * @author	Bryce Standley
        * @date	12/09/2021
        * 
        * @return bool If the renderer is enabled
        *
        */
        static bool IsColliderRenderingEnabled();

        /**
         * @fn	static std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> PhysicsEngine::GetColliderRenderObjects();
         *
         * @brief	Gets collider render objects by using a pair to retreive the VAO and VBO data for lines and triangles
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The collider render objects.
         */
        static std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> GetColliderRenderObjects();

        /**
         * @fn	static Ref<Shader> PhysicsEngine::GetColliderShader();
         *
         * @brief	Gets collider shader
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The collider shader.
         */
        static Ref<Shader> GetColliderShader();

        /**
         * @fn	static void PhysicsEngine::UpdateColliderRenderer();
         *
         * @brief	Updates the collider renderer
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */
        static void UpdateColliderRenderer();

        /**
         * @fn	static rp3d::DebugRenderer* PhysicsEngine::GetColliderRenderer();
         *
         * @brief	Gets collider renderer
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The collider renderer.
         */
        static rp3d::DebugRenderer* GetColliderRenderer();

        /**
         * @fn	static void PhysicsEngine::PhysicsLoggerInit();
         *
         * @brief	Initialise the physics logger
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */
        static void PhysicsLoggerInit();

        /**
         * @brief Processes collisions in the CollisionDetectionEngine collision queue
         * @author Bryce Standley
         * @date 06-11-2021
         */
        static void ProcessCollisions();

        /**
         * @brief Processes velocities for all RigidBody objects in the world
         * @author Bryce Standley
         * @date 06-11-2021
         */
        static void ProcessRigidbodyVelocities(const Timestep& deltaTime, entt::registry& componentRegistry);

        /**
         * @brief Processes position and orientations for all RigidBody objects in the world
         * @author Bryce Standley
         * @date 06-11-2021
         */
        static void ProcessRigidbodyPositions(const Timestep& deltaTime, entt::registry& componentRegistry);

        /**
         * @brief Resets external force and torque applied to Rigidbody objects in the world
         * @author Bryce Standley
         * @date 06-11-2021
         */
        static void ResetRigidbodyForcesAndTorques(entt::registry& componentRegistry);

        /**
         * @brief Updates the inertia tensor of each RigidBody object in the world
         * @author Bryce Standley
         * @date 06-11-2021
         */
        static void UpdateInertiaTensor(entt::registry& componentRegistry);

        /**
         * @brief Updates all state and transform values for React on each RigidBody in the world
         * @author Bryce Standley
         * @date 06-11-2021
         */
        static void UpdateBodies(entt::registry& componentRegistry);

        /**
         * @brief Updates and checks each RigidBody object in the world if it can be put to sleep
         * @author Bryce Standley
         * @date 06-11-2021
         */
        static void UpdateSleepState(entt::registry& componentRegistry, Timestep deltaTime);
    
    private:
     
        /** @brief a static reference to the active physics manager */
        static Ref<PhysicsManager> m_PhysicsManager;

        /** @brief Transform used for rendering the colliders within the scene*/
        static TransformComponent m_ColliderTransform;

        friend class tnah::Scene;
        friend class tnah::Renderer;
    };

#pragma endregion PhysicsEngine

}
