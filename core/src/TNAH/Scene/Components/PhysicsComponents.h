#pragma once

#include "TNAH/Physics/PhysicsEngine.h"

#include "TNAH/Renderer/Mesh.h"
#include "ComponentIdentification.h"

namespace tnah{

class GameObject;
	
	/**********************************************************************************************//**
 * @class	RigidBodyComponent
 *
 * @brief	A physics rigidbody allows physics to be simulated on a object
 *
 * @author	Bryce Standley
 * @date	20/07/2021
 * 			
 * @author	Christopher Logan
 * @date	05/09/2021
 **************************************************************************************************/

	struct RigidBodyComponent
	{
		Ref<Physics::RigidBody> Body = nullptr;
		
		/** @brief	True to edit */
		bool Edit = false;
		/** @brief	True to use edit */
		bool UseEdit = false;

		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		RigidBodyComponent();

		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent(const RigidBodyComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		RigidBodyComponent(const RigidBodyComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn		RigidBodyComponent(GameObject& gameObject, const Physics::BodyType& type = Physics::BodyType::Dynamic);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	gameObject	
		 * @param 	type	 	The type.
		 **************************************************************************************************/

		RigidBodyComponent(GameObject& gameObject, const Physics::BodyType& type = Physics::BodyType::Dynamic);
		

		/**********************************************************************************************//**
		* @fn	RigidBodyComponent::void OnUpdate(const TransformComponent& transform);
		*
		* @brief	Update function for the Rigidbody component. Updates the Rigidbody with the current transform and orientation.
		*
		* @author	Bryce Standley
		* @date	10/10/2021
		*
		**************************************************************************************************/
		void OnUpdate(TransformComponent& transform);
		
		/**********************************************************************************************//**
		 * @fn	void ApplyForce(const glm::vec3& direction, const glm::vec3& force);
		 *
		 * @brief	Applies the force
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	direction 	The direction.
		 * @param 	force	  	The force.
		 **************************************************************************************************/

		void ApplyForce(const glm::vec3& direction, const glm::vec3& force);

		/**********************************************************************************************//**
		 * @fn	void ApplyTorque(const glm::vec3& direction, const glm::vec3& torque);
		 *
		 * @brief	Applies the torque described by torque
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	torque	The torque.
		 **************************************************************************************************/

		void ApplyTorque(const glm::vec3& direction, const glm::vec3& torque);

		
		/**
		 * @fn Ref<Physics::Collider> AddCollider(const glm::vec3& boxSize);
		 * 
		 * @brief Adds a collider to the current active rigidbody on the component.
		 *
		 * @author Bryce Standley
		 * @date Thursday, 14 October 2021
		 * 
		 * @param boxSize Full size of each dimension of the box
		 *
		 * @returns  Collider Ref or nullptr if adding the collider failed.
		 *
		 */
		Ref<Physics::Collider> AddCollider(const glm::vec3& boxSize);

		/**
		* @fn Ref<Physics::Collider> AddCollider(const glm::vec3& boxSize, const glm::vec3& localPosition, const glm::quat& localOrientation, const float& density, const float& volume);
		*
		* @brief Adds a collider with set values
		*
		* @author Bryce Standley
		* @date 6/11/2021
		*
		* @param boxSize
		* @param localPosition
		* @param localOrientation
		* @param density
		* @param volume
		* @return 
		*
		*/
		Ref<Physics::Collider> AddCollider(const glm::vec3& boxSize, const glm::vec3& localPosition, const glm::quat& localOrientation, const float& density, const float& volume);

		
		/**
		 * @fn Ref<Physics::Collider> AddCollider(const float& sphereRadius);
		 * 
		 * @brief Adds a collider to the current active rigidbody on the component.
		 *
		 * @author Bryce Standley
		 * @date Thursday, 14 October 2021
		 * 
		 * @param sphereRadius The radius of the sphere
		 *
		 * @returns  Collider Ref or nullptr if adding the collider failed.
		 *
		 */
		Ref<Physics::Collider> AddCollider(const float& sphereRadius);

		/**
		* @fn Ref<Physics::Collider> AddCollider(const float& sphereRadius, const glm::vec3& localPosition, const glm::quat& localOrientation, const float& density, const float& volume);
		*
		* @brief Adds a sphere collider with set values
		*
		* @author Bryce Standley
		* @date 6/11/2021
		*
		* @param sphereRadius
		* @param localPosition
		* @param localOrientation
		* @param density
		* @param volume
		* @return 
		*
		*/
		Ref<Physics::Collider> AddCollider(const float& sphereRadius, const glm::vec3& localPosition, const glm::quat& localOrientation, const float& density, const float& volume);

		
		/**
		 * @fn Ref<Physics::Collider> AddCollider(const float& capsuleRadius, const float& capsuleHeight);
		 * 
		 * @brief Adds a collider to the current active rigidbody on the component.
		 *
		 * @author Bryce Standley
		 * @date Thursday, 14 October 2021
		 * 
		 * @param capsuleRadius The radius of the capsule
		 * @param capsuleHeight The height of the capsule
		 *
		 * @returns  Collider Ref or nullptr if adding the collider failed.
		 *
		 */
		Ref<Physics::Collider> AddCollider(const float& capsuleRadius, const float& capsuleHeight);

		/**
		* @fn Ref<Physics::Collider> AddCollider(const float& capsuleRadius, const float& capsuleHeight, const glm::vec3& localPosition, const glm::quat& localOrientation, const float& density, const float& volume);
		*
		* @brief Adds a capsule collider with set values
		*
		* @author Bryce Standley
		* @date 6/11/2021
		*
		* @param capsuleRadius
		* @param capsuleHeight
		* @param localPosition
		* @param localOrientation
		* @param density
		* @param volume
		* @return 
		*
		*/
		Ref<Physics::Collider> AddCollider(const float& capsuleRadius, const float& capsuleHeight, const glm::vec3& localPosition, const glm::quat& localOrientation, const float& density, const float& volume);

		
	private:
		/** @brief	Search string for the component in the editor */
		inline static std::string s_SearchString = "rigidbody component";
		/** @brief	Component search types and groupings  */
		inline static ComponentTypes s_Types = {
			{ComponentVariations::Rigidbody},
		{{ComponentCategory::Physics}}
		};
		
		friend class EditorUI;
	};

}
