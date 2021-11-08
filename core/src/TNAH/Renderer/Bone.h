#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <string>
#include <Assimp/anim.h>

namespace tnah {

	/**
	 * @struct	KeyPosition
	 *
	 * @brief	A key position.
	 *
	 * @author	Dylan Blereau
	 * @date	12/09/2021
	 */

	struct KeyPosition 
	{

		/** @brief	The position */
		glm::vec3 position;

		/** @brief	The time stamp */
		float timeStamp;
	};

	/**
	 * @struct	KeyRotation
	 *
	 * @brief	A key rotation.
	 *
	 * @author	Dylan Blereau
	 * @date	12/09/2021
	 */

	struct KeyRotation
	{

		/** @brief	The orientation */
		glm::quat orientation;

		/** @brief	The time stamp */
		float timeStamp;
	};

	/**
	 * @struct	KeyScale
	 *
	 * @brief	A key scale.
	 *
	 * @author	Dylan Blereau
	 * @date	12/09/2021
	 */

	struct KeyScale
	{

		/** @brief	The scale */
		glm::vec3 scale;

		/** @brief	The time stamp */
		float timeStamp;
	};

	/**
	 * @class	Bone
	 *
	 * @brief	A bone class responsible for handling the bones used in animation 
	 *
	 * @author	Dylan Blereau
	 * @date	12/09/2021
	 */

	class Bone 
	{
	private:

		/** @brief	The positions */
		std::vector<KeyPosition> m_Positions;

		/** @brief	The rotations */
		std::vector<KeyRotation> m_Rotations;

		/** @brief	The scales */
		std::vector<KeyScale> m_Scales;

		/** @brief	Number of positions */
		int m_NumPositions;

		/** @brief	Number of rotations */
		int m_NumRotations;

		/** @brief	Number of scalings */
		int m_NumScalings;

		/** @brief	The local transform */
		glm::mat4 m_LocalTransform;

		/** @brief	The name */
		std::string m_Name;

		/** @brief	The identifier */
		int m_ID;

	public:

		/**
		 * @fn	Bone::Bone(const std::string& name, int ID, const aiNodeAnim* channel)
		 *
		 * @brief	Constructor that reads keyframes from aiNodeAnim.
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	name   	The name.
		 * @param 	ID	   	The identifier.
		 * @param 	channel	The channel.
		 */

		Bone(const std::string& name, int ID, const aiNodeAnim* channel) : m_Name(name), m_ID(ID), m_LocalTransform(1.0f) 
		{
			m_NumPositions = channel->mNumPositionKeys;

			for (int positionIndex = 0; positionIndex < m_NumPositions; ++positionIndex)
			{
				aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
				float timeStamp = channel->mPositionKeys[positionIndex].mTime;
				KeyPosition data;
				//data.position = AssimpGLMHelpers::GetGLMVec(aiPosition);
				data.timeStamp = timeStamp;
				m_Positions.push_back(data);
			}

			m_NumRotations = channel->mNumRotationKeys;

			for (int rotationIndex = 0; rotationIndex < m_NumRotations; ++rotationIndex) 
			{
				aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
				float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
				KeyRotation data;
				//data.orientation = AssimpGLMHelpers::GetGLMQuat(aiOrientation);
				data.timeStamp = timeStamp;
				m_Rotations.push_back(data);
			}

			m_NumScalings = channel->mNumScalingKeys;

			for (int keyIndex = 0; keyIndex < m_NumScalings; ++keyIndex) 
			{
				aiVector3D scale = channel->mScalingKeys[keyIndex].mValue;
				float timeStamp = channel->mScalingKeys[keyIndex].mTime;
				KeyScale data;
				//data.scale = AssimpGLMHelpers::GetGLMVec(scale);
				data.timeStamp = timeStamp;
				m_Scales.push_back(data);
			}
		}

		/* Interpolates b/w positions,rotations & scaling keys based on the curren time of the
		animation and prepares the local transformation matrix by combining all keys tranformations */

		/**
		 * @fn	void Bone::Update(float animationTime)
		 *
		 * @brief	Updates the given animationTime by interpolating between position, rotation, scale and combining them all together to form the localTransform
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	animationTime	The animation time.
		 */

		void Update(float animationTime) 
		{
			glm::mat4 translation = InterpolatePosition(animationTime);
			glm::mat4 rotation = InterpolateRotation(animationTime);
			glm::mat4 scale = InterpolateScaling(animationTime);
			m_LocalTransform = translation * rotation * scale;
		}

		/**
		 * @fn	glm::mat4 Bone::GetLocalTransform()
		 *
		 * @brief	Gets local transform
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The local transform.
		 */

		glm::mat4 GetLocalTransform() { return m_LocalTransform; }

		/**
		 * @fn	std::string Bone::GetBoneName() const
		 *
		 * @brief	Gets bone name
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The bone name.
		 */

		std::string GetBoneName() const { return m_Name; }

		/**
		 * @fn	int Bone::GetBoneID()
		 *
		 * @brief	Gets bone identifier
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The bone identifier.
		 */

		int GetBoneID() { return m_ID; }

		/**
		 * @fn	int Bone::GetPositionIndex(float animationTime)
		 *
		 * @brief	Gets the index of the position to interpolate to based on the current animation time
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	animationTime	The animation time.
		 *
		 * @returns	The position index.
		 */

		int GetPositionIndex(float animationTime)
		{
			for (int index = 0; index < m_NumPositions - 1; ++index) 
			{
				if (animationTime < m_Positions[index + 1].timeStamp)
					return index;
			}
			assert(0);
			return 0;
		}

		/**
		 * @fn	int Bone::GetRotationIndex(float animationTime)
		 *
		 * @brief	Gets the index of the rotation to interpolate to based on the current animation time
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	animationTime	The animation time.
		 *
		 * @returns	The rotation index.
		 */

		int GetRotationIndex(float animationTime)
		{
			for (int index = 0; index < m_NumRotations - 1; ++index)
			{
				if (animationTime < m_Rotations[index + 1].timeStamp)
					return index;
			}
			assert(0);
			return 0;
		}

		/**
		 * @fn	int Bone::GetScaleIndex(float animationTime)
		 *
		 * @brief	Gets the index of the scale to interpolate to based on the current animation time
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	animationTime	The animation time.
		 *
		 * @returns	The scale index.
		 */

		int GetScaleIndex(float animationTime)
		{
			for (int index = 0; index < m_NumScalings - 1; ++index)
			{
				if (animationTime < m_Scales[index + 1].timeStamp)
					return index;
			}
			assert(0);
			return 0;
		}

		private:

			/**
			 * @fn	float Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
			 *
			 * @brief	Gets scale factor
			 *
			 * @author	Dylan Blereau
			 * @date	12/09/2021
			 *
			 * @param 	lastTimeStamp	The last time stamp.
			 * @param 	nextTimeStamp	The next time stamp.
			 * @param 	animationTime	The animation time.
			 *
			 * @returns	The scale factor.
			 */

			float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime) 
			{
				float scaleFactor = 0.0f;
				float midWayLength = animationTime - lastTimeStamp;
				float framesDiff = nextTimeStamp - lastTimeStamp;
				scaleFactor = midWayLength / framesDiff;
				return scaleFactor;
			}

			/**
			 * @fn	glm::mat4 Bone::InterpolatePosition(float animationTime)
			 *
			 * @brief	Interpolate position
			 *
			 * @author	Dylan Blereau
			 * @date	12/09/2021
			 *
			 * @param 	animationTime	The animation time.
			 *
			 * @returns	A glm::mat4.
			 */

			glm::mat4 InterpolatePosition(float animationTime) 
			{
				if (1 == m_NumPositions)
					return glm::translate(glm::mat4(1.0f), m_Positions[0].position);

				int p0Index = GetPositionIndex(animationTime);
				int p1Index = p0Index + 1;
				float scaleFactor = GetScaleFactor(m_Positions[p0Index].timeStamp, m_Positions[p1Index].timeStamp, animationTime);
				
				glm::vec3 finalPosition = glm::mix(m_Positions[p0Index].position, m_Positions[p1Index].position, scaleFactor);

				return glm::translate(glm::mat4(1.0f), finalPosition);
			}

			/**
			 * @fn	glm::mat4 Bone::InterpolateRotation(float animationTime)
			 *
			 * @brief	Interpolate rotation
			 *
			 * @author	Dylan Blereau
			 * @date	12/09/2021
			 *
			 * @param 	animationTime	The animation time.
			 *
			 * @returns	A glm::mat4.
			 */

			glm::mat4 InterpolateRotation(float animationTime) 
			{
				if (1 == m_NumRotations) 
				{
					auto rotation = glm::normalize(m_Rotations[0].orientation);
					return glm::toMat4(rotation);
				}

				int p0Index = GetRotationIndex(animationTime);
				int p1Index = p0Index + 1;
				float scaleFactor = GetScaleFactor(m_Rotations[p0Index].timeStamp, m_Rotations[p1Index].timeStamp, animationTime);

				glm::quat finalRotation = glm::slerp(m_Rotations[p0Index].orientation, m_Rotations[p1Index].orientation, scaleFactor);
				finalRotation = glm::normalize(finalRotation);
				return glm::toMat4(finalRotation);
			}

			/**
			 * @fn	glm::mat4 Bone::InterpolateScaling(float animationTime)
			 *
			 * @brief	Interpolate scaling
			 *
			 * @author	Dylan Blereau
			 * @date	12/09/2021
			 *
			 * @param 	animationTime	The animation time.
			 *
			 * @returns	A glm::mat4.
			 */

			glm::mat4 InterpolateScaling(float animationTime) 
			{
				if (1 == m_NumScalings)
					return glm::scale(glm::mat4(1.0f), m_Scales[0].scale);

				int p0Index = GetScaleIndex(animationTime);
				int p1Index = p0Index + 1;
				float scaleFactor = GetScaleFactor(m_Scales[p0Index].timeStamp, m_Scales[p1Index].timeStamp, animationTime);

				glm::vec3 finalScale = glm::mix(m_Scales[p0Index].scale, m_Scales[p1Index].scale, scaleFactor);

				return glm::scale(glm::mat4(1.0f), finalScale);
			}







	};

}