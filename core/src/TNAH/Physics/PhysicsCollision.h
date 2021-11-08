#pragma once
#include <queue>
#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>
#pragma warning(pop)

#include "Rigidbody.h"


namespace tnah {

	class GameObject;
	
	namespace Physics {

		/**
		 * @class PhysicsCollision
		 * @brief Class to hold information about a collision
		 * @author Bryce Standley
		 * @date 06-11-2021
		 */
		class PhysicsCollision
		{
		public:

			/**
			 * @class CollisionData
			 * @brief Internal Class to hold collision data
			 * @author Bryce Standley
			 * @date 06-11-2021
			 */
			class CollisionData
			{
			public:
				/**
				 * @brief Get the Contact Point object
				 * @author Bryce Standley
				 * @date 06-11-2021
				 * @return glm::vec3 
				 */
				glm::vec3 GetContactPoint() const { return m_ContactPoint; }

				/**
				 * @brief Get the Contact Normal object
				 * @author Bryce Standley
				 * @date 06-11-2021
				 * @return glm::vec3 
				 */
				glm::vec3 GetContactNormal() const { return m_ContactNormal; }

				/**
				 * @brief Get the Penetration object
				 * @author Bryce Standley
				 * @date 06-11-2021
				 * @return float 
				 */
				float GetPenetration() const { return m_PenetrationDepth; }
				
				/**
				 * @brief Get the Contact Positions object
				 * @author Bryce Standley
				 * @date 06-11-2021
				 * @return std::pair<glm::vec3, glm::vec3> 
				 */
				std::pair<glm::vec3, glm::vec3> GetContactPositions() { return {m_Body1ContactPosition, m_Body2ContactPosition}; }

				/**
				 * @brief Get the Game Objects object
				 * @author Bryce Standley
				 * @date 06-11-2021
				 * @return std::pair<GameObject*, GameObject*> 
				 */
				std::pair<GameObject*, GameObject*> GetGameObjects() { return {m_Body1GameObject, m_Body2GameObject}; }

				/**
				 * @brief Get the Rigid Bodies object
				 * @author Bryce Standley
				 * @date 06-11-2021
				 * @return std::pair<Ref<RigidBody>, Ref<RigidBody>> 
				 */
				std::pair<Ref<RigidBody>, Ref<RigidBody>> GetRigidBodies() { return {m_Body1RigidBody, m_Body2RigidBody}; }
			
			private:
				/**
				 * @brief Contact point of the collision
				 * @author Bryce Standley
				 * @date 06-11-2021
				 */
				glm::vec3 m_ContactPoint = {0,0,0};

				/**
				 * @brief Contact normal of the collision
				 * @author Bryce Standley
				 * @date 06-11-2021
				 */
				glm::vec3 m_ContactNormal = {0,0,0};
			
				/**
				 * @brief Position of body 1 on contact
				 * @author Bryce Standley
				 * @date 06-11-2021
				 */
				glm::vec3 m_Body1ContactPosition = {0,0,0};

				/**
				 * @brief Position of body 2 on contact
				 * @author Bryce Standley
				 * @date 06-11-2021
				 */
				glm::vec3 m_Body2ContactPosition = {0,0,0};

				/**
				 * @brief Depth the bodies penetrated when detected
				 * @author Bryce Standley
				 * @date 06-11-2021
				 */
				float m_PenetrationDepth = 0.0f;

				/**
				 * @brief Pointer to body 1's GameObject
				 * @author Bryce Standley
				 * @date 06-11-2021
				 */
				GameObject* m_Body1GameObject = nullptr;

				/**
				 * @brief Pointer to body 2's GameObject
				 * @author Bryce Standley
				 * @date 06-11-2021
				 */
				GameObject* m_Body2GameObject = nullptr;

				/**
				 * @brief Ref to body 1's RigidBody
				 * @author Bryce Standley
				 * @date 06-11-2021
				 */
				Ref<RigidBody> m_Body1RigidBody = nullptr;

				/**
				 * @brief Ref to body 2's Rigidbody
				 * @author Bryce Standley
				 * @date 06-11-2021
				 */
				Ref<RigidBody> m_Body2RigidBody = nullptr;

				friend class PhysicsCollision;
			};
			
			/**
			 * @brief Construct a new Physics Collision object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 */
			PhysicsCollision();
			
			/**
			 * @brief Construct a new Physics Collision object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 */
			PhysicsCollision(rp3d::CollisionCallback::ContactPair contactPair);

			/**
			 * @brief Get the Total Contact Points object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 * @return uint32_t 
			 */
			uint32_t GetTotalContactPoints() const { return m_TotalContactPoints; }
			
			/**
			 * @brief Get the Collision Data object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 * @return std::queue<CollisionData>& 
			 */
			std::queue<CollisionData>& GetCollisionData() { return m_CollisionData; }
 
		private:

		/**
		 * @brief Total Contact points in the collision
		 * @author Bryce Standley
		 * @date 06-11-2021
		*/
			uint32_t m_TotalContactPoints = 0;
			
			/**
			 * @var m_CollisionData
			 *
			 * @brief A queue holding data about a collision.
			 */
			std::queue<CollisionData> m_CollisionData;
			
		};
	}
}