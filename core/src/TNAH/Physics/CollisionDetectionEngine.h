#pragma once

#include "PhysicsCollision.h"
#include "TNAH/Physics/PhysicsTimestep.h"

#include <queue>

namespace tnah {
	namespace Physics {
		
		/**
		 * @class CollisionDetectionEngine
		 * @brief Class to wrap and construct collision information
		 * @author Bryce Standley
		 * @date 06-11-2021
		 */
		class CollisionDetectionEngine : public RefCounted
		{
		public:
			/**
			 * @brief Creates a Ref to the collision detection engine
			 * @author Bryce Standley
			 * @date 06-11-2021
			 * @return Ref<CollisionDetectionEngine> 
			 */
			static Ref<CollisionDetectionEngine> Create();
			
			/**
			 * @brief Construct a new Collision Detection Engine object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 */
			CollisionDetectionEngine();
			
			/**
			 * @brief Fixed update loop function to update the physics world
			 * @author Bryce Standley
			 * @date 06-11-2021
			 */
			void FixedUpdate(rp3d::PhysicsWorld* physicsWorld, PhysicsTimestep physTime);

			/**
			 * @brief Get the Current Collisions object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 * @return std::queue<PhysicsCollision>& 
			 */
			std::queue<PhysicsCollision>& GetCurrentCollisions() { return m_CurrentCollisions; }

			/**
			 * @brief Registers a collision into the collision queue
			 * @author Bryce Standley
			 * @date 06-11-2021
			 */
			void RegisterCollision(PhysicsCollision collision) { m_CurrentCollisions.push(collision); }

		private:

			/**
			 * @var m_CurrentCollisions
			 * @brief Queue of current collisions
			 * @author Bryce Standley
			 * @date 06-11-2021
			 */
			std::queue<PhysicsCollision> m_CurrentCollisions;
		};
		
	}
}
