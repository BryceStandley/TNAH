#pragma once

#include "PhysicsStructures.h"
#include "TNAH/Core/Math.h"

#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>
#pragma warning(pop)

namespace tnah::Physics {

		/**
		 * @class Collider
		 * @brief Class to contain the required information about Colliders
		 * @author Bryce Standley
		 * @date 06-11-2021
		 */
		class Collider : public RefCounted
		{
		public:
			/**
			* @enum Type
			*
			* @brief Different type flag enum.
			*
			* @author Bryce Standley
			* @date 6/11/2021
			*
			*/
			enum class Type
			{
				Box, Sphere, Capsule
			};

			/**
			* @fn tnah::Physics::Collider::Collider();
			*
			* @brief Constructor
			*
			* @author Bryce Standley
			* @date 6/11/2021
			*
			*/
			Collider();

			/**
			Collider(rp3d::CollisionShape* collider, Type type);
			*
			* @brief Constructor
			*
			* @author Bryce Standley
			* @date 6/11/2021
			*
			* @param collider
			* @param type
			* @return 
			*
			**/
			Collider(rp3d::CollisionShape* collider, Type type);

			/**
			* @fn tnah::Ref<tnah::Physics::Collider> Create(rp3d::CollisionShape* collider);
			*
			* @brief Constructor of Ref
			*
			* @author Bryce Standley
			* @date 6/11/2021
			*
			* @param collider
			* @return collider Ref
			*
			*/
			static Ref<Collider> Create(rp3d::CollisionShape* collider, Type type);

			/**
			* @fn void Collider::SetPosition(const glm::vec3& position);
			*
			* @brief Sets the position value
			*
			* @author Bryce Standley
			* @date 6/11/2021
			*
			* @param position
			* @return void
			*
			*/
			void SetPosition(const glm::vec3& position) { m_LocalPosition = position; }

			/**
			* @fn void SetOrientation(const glm::quat& orientation);
			*
			* @brief Sets the orientation value
			*
			* @author Bryce Standley
			* @date 6/11/2021
			*
			* @param orientation
			* @return void
			*
			*/
			void SetOrientation(const glm::quat& orientation) { m_LocalOrientation = orientation; }

			/**
			 * @fn glm::vec3 GetColliderPosition() const 
			 * 
			 *
			 * @brief Get the Collider Position object
			 * 
			 * @author Bryce Standley
			 * 
			 * @return glm::vec3 
			 */
			glm::vec3 GetColliderPosition() const { return m_LocalPosition; }

			/**
			 * @fn glm::quat GetColliderOrientation() const 
			 * 
			 *
			 * @brief Get the Collider Orientation object
			 * 
			 * @author Bryce Standley
			 * 
			 * @return glm::quat 
			 */
			glm::quat GetColliderOrientation() const { return m_LocalOrientation; }
			
			/**
			 * @fn BodyMass& GetColliderMass() 
			 * 
			 *
			 * @brief Get the Collider Mass object
			 * 
			 * @author Bryce Standley
			 * 
			 * @return BodyMass& 
			 */
			BodyMass& GetColliderMass() { return m_Mass; }

			/**
			 * @brief Get the Type object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 * @return Type 
			 */
			Type GetType() const { return m_Type; }

			/**
			 * @brief Get the Collision Shape Pair object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 * @return std::pair<Type, rp3d::CollisionShape*> 
			 */
			std::pair<Type, rp3d::CollisionShape*> GetCollisionShapePair() { return { m_Type, m_Collider }; }

			/**
			 * @brief Get the Local Collider Inertia Tensor object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 * @return glm::vec3 
			 */
			glm::vec3 GetLocalColliderInertiaTensor();

			/**
			 * @brief Get the Volume object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 * @return float 
			 */
			float GetVolume() { return m_Volume; }

			/**
			 * @brief Set the Volume object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 */
			void SetVolume(const float value) { m_Volume = value; }
			
			/**
			 * @brief Get the Density object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 * @return float 
			 */
			float GetDensity() { return m_Density; }

			/**
			 * @brief Set the Density object
			 * @author Bryce Standley
			 * @date 06-11-2021
			 */
			void SetDensity(const float value) { m_Density = value; }

		private:

			/**
			 * @fn void InitializeBox();
			 *
			 * @brief Sets us the local mass values of the Collider based on the BoxShape.
			 * @author  Bryce Standley
			 */
			void InitializeBox();

			/**
			* @fn void InitializeSphere();
			*
			* @brief Sets us the local mass values of the Collider based on the SphereShape.
			* @author  Bryce Standley
			*/
			void InitializeSphere();

			/**
			* @fn void InitializeCapsule();
			*
			* @brief Sets us the local mass values of the Collider based on the CapsuleShape.
			* @author  Bryce Standley
			*/
			void InitializeCapsule();

			

		private:
			/**
			* @var m_Collider
			*
			* @brief The Reactphysics3D CollisionShape. This needs to be reinterpreted into a BoxShape or SphereShape depending on the ColliderType.
			*/
			rp3d::CollisionShape* m_Collider = nullptr;

			/**
			* @var m_Type
			*
			* @brief The type of the Collider. Either Box or Sphere currently.
			*/
			Type m_Type = Type::Box;

			/**
			* @var m_LocalPosition
			*
			* @brief The position of the Collider locally to its parent Rigidbody.
			* @note The position should always be at 0,0,0 ie the centre of the Rigidbody.
			* @note However the position should be changed if the object requires multiple colliders with different positions relative to the Rigidbody.
			*/
			glm::vec3 m_LocalPosition = {};

			/**
			* @var m_LocalOrientation
			*
			* @brief The orientation of the Collider locally to its parent Rigidbody.
			*/
			glm::quat m_LocalOrientation = {};

			/**
			* @var m_Mass
			*
			* @brief The local BodyMass information for this Collider.
			*/
			BodyMass m_Mass;

			/**
			 * @var m_InertiaTensor
			 * 
			 * @brief The Inertia tensor of the collider
			 */
			InertiaTensor m_InertiaTensor;

			/**
			 * @var m_ID
			 * @brief Id of the collider
			 * @author Bryce Standley
			 * @date 06-11-2021
			 */
			uint32_t m_ID = 0;

			/**
			 * @var m_Volume
			 *
			 * @brief The volume of the collider in meters cubed.
			 */
			float m_Volume = 0.0f;

			/**
			* @var m_Density
			*
			* @brief The density of the colliders material in kg per meter cubed. Default 1000kg/m3 ie the density of water.
			*/
			float m_Density = 1.0f;
			
			friend class PhysicsEngine;
			friend class EditorUI;
			friend class Serializer;
		};
	
}
