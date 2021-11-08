#pragma once

#include "AssimpGLMHelpers.h"
#include "TNAH/Core/Core.h"
#include <Assimp/scene.h>

#include "Bone.h"
#include "BoneInfo.h"

namespace tnah  {

	/**
	 * @struct	AssimpNodeData
	 *
	 * @brief	A struct containing the Assimp node data
	 *
	 * @author	Dylan Blereau
	 * @date	12/09/2021
	 */

	struct AssimpNodeData 
	{

		AssimpNodeData()
		{
			children.reserve(1);
		}

		/** @brief	The transformation */
		glm::mat4 transformation = glm::mat4(1.0f);

		/** @brief	The name */
		std::string name = "";

		/** @brief	Number of childrens */
		int childrenCount = 0;

		/** @brief	The children */
		std::vector<AssimpNodeData> children;
	};

	/**
	 * @class	Animation
	 *
	 * @brief	An animation class responsible for the skeletal animation
	 *
	 * @author	Dylan Blereau
	 * @date	12/09/2021
	 */

	class Animation
	{
	public:

		/**
		 * @fn	Animation::Animation() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 */

		Animation() = default;

		/**
		 * @fn	Animation::Animation(const aiScene* scene)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	scene	The scene.
		 */

		Animation(const aiScene* scene) 
		{
			m_Animation = scene->mAnimations[0];
			m_Duration = m_Animation->mDuration;
			m_TicksPerSecond = m_Animation->mTicksPerSecond;
			ReadHeirarchyData(m_RootNode, scene->mRootNode);
		}

		/**
		 * @fn	Animation::~Animation()
		 *
		 * @brief	Destructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 */

		~Animation() {}

		/**
		 * @fn	Bone* Animation::FindBone(const std::string& name)
		 *
		 * @brief	Searches for the first bone
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	name	The name.
		 *
		 * @returns	Null if it fails, else the found bone.
		 */

		Bone* FindBone(const std::string& name) 
		{
			auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),
				[&](const Bone& Bone)
				{
					return Bone.GetBoneName() == name;
				}
			);
			if (iter == m_Bones.end()) return nullptr;
			else return &(*iter);
		}

		/**
		 * @fn	inline float Animation::GetTicksPerSecond()
		 *
		 * @brief	Gets ticks per second
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The ticks per second.
		 */

		inline float GetTicksPerSecond() { return m_TicksPerSecond; }

		/**
		 * @fn	inline float Animation::GetDuration()
		 *
		 * @brief	Gets the duration
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The duration.
		 */

		inline float GetDuration() { return m_Duration; }

		/**
		 * @fn	inline const AssimpNodeData& Animation::GetRootNode()
		 *
		 * @brief	Gets root node
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The root node.
		 */

		inline const AssimpNodeData& GetRootNode() { return m_RootNode; }

		/**
		 * @fn	inline const std::map<std::string, BoneInfo>& Animation::GetBoneIDMap()
		 *
		 * @brief	Gets bone identifier map
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The bone identifier map.
		 */

		inline const std::map<std::string, BoneInfo>& GetBoneIDMap() 
		{
			return m_BoneInfoMap;
		}

		/**
		 * @fn	void Animation::ReadMissingBones(std::map<std::string, BoneInfo>& boneInfoMap, int& boneCount)
		 *
		 * @brief	Reads missing bones
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param [in,out]	boneInfoMap	The bone information map.
		 * @param [in,out]	boneCount  	Number of bones.
		 */

		void ReadMissingBones(std::map<std::string, BoneInfo>& boneInfoMap, int& boneCount) 
		{
			int size = m_Animation->mNumChannels;

			//reading channels (bone engaged in an animation and their keyframes)
			for (int i = 0; i < size; i++) 
			{
				auto channel = m_Animation->mChannels[i];
				std::string boneName = channel->mNodeName.data;
				
				if (boneInfoMap.find(boneName) == boneInfoMap.end())
				{
					boneInfoMap[boneName].id = boneCount;
					boneCount++;
				}
				m_Bones.push_back(Bone(channel->mNodeName.data, boneInfoMap[channel->mNodeName.data].id, channel));
			}

			m_BoneInfoMap = boneInfoMap;
		}
	
	private:

		/**
		 * @fn	void Animation::ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src)
		 *
		 * @brief	Reads heirarchy data
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param [in,out]	dest	Destination for the.
		 * @param 		  	src 	Source for the.
		 */

		void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src) 
		{
			assert(src);

			dest.name = src->mName.data;
			dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
			dest.childrenCount = src->mNumChildren;

			for (int i = 0; i < src->mNumChildren; i++) 
			{
				AssimpNodeData newData;
				ReadHeirarchyData(newData, src->mChildren[i]);
				dest.children.push_back(newData);
			}
		}


		/** @brief	The duration of the animation */
		float m_Duration = 0.0f;

		/** @brief	The ticks per second, which notes how fast interpolation between frames should be */
		int m_TicksPerSecond = 0.0f;

		/** @brief	The bones required for the animation */
		std::vector<Bone> m_Bones;

		/** @brief	The root node */
		AssimpNodeData m_RootNode;

		/** @brief	The bone information map */
		std::map<std::string, BoneInfo> m_BoneInfoMap;

		/** @brief	The animation */
		aiAnimation* m_Animation;
		

	};
}
