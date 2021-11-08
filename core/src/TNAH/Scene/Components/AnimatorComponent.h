#pragma once

#include "TNAH/Renderer/Animation.h"

namespace tnah 
{
	/**********************************************************************************************//**
	 * @class	AnimatorComponent
	 *
	 * @brief	An animator component.
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 **************************************************************************************************/

	class AnimatorComponent 
	{
	public:

		/**********************************************************************************************//**
		 * @fn	AnimatorComponent::AnimatorComponent();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		AnimatorComponent();

		/**********************************************************************************************//**
		 * @fn	AnimatorComponent::AnimatorComponent(const Animation& animation);
		 *
		 * @brief	Copy Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	animation	The animation.
		 **************************************************************************************************/

		AnimatorComponent(const Animation& animation);

		/**********************************************************************************************//**
		 * @fn	void AnimatorComponent::UpdateAnimation(float dt);
		 *
		 * @brief	Updates the animation dictated by deltaTime (dt)
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	dt	The deltaTime
		 **************************************************************************************************/

		void UpdateAnimation(float dt);

		/**********************************************************************************************//**
		 * @fn	void AnimatorComponent::PlayAnimation(const Animation& animation);
		 *
		 * @brief	Plays animation
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	animation	The animation component.
		 **************************************************************************************************/

		void PlayAnimation(const Animation& animation);

		/**********************************************************************************************//**
		 * @fn	std::vector<glm::mat4> AnimatorComponent::GetFinalBonesMatrices() const
		 *
		 * @brief	Gets final bones matrices
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The final bones matrices.
		 **************************************************************************************************/

		std::vector<glm::mat4> GetFinalBonesMatrices() const { return m_FinalBoneMatrices; };

	private:

		/**********************************************************************************************//**
		 * @fn	void AnimatorComponent::CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
		 *
		 * @brief	Calculates the bone transform
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	node		   	The node.
		 * @param 	parentTransform	The parent transform.
		 **************************************************************************************************/

		void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
	
	private:

		/** @brief	The final bone matrices */
		std::vector<glm::mat4> m_FinalBoneMatrices;

		/** @brief	The current animation */
		Animation m_CurrentAnimation;

		/** @brief	The current time */
		float m_CurrentTime = 0;


		/** @brief	The delta time */
		float m_DeltaTime = 0;
	};



}