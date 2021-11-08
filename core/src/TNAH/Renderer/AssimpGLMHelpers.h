#pragma once

#include<assimp/Quaternion.h>
#include<assimp/vector3.h>
#include<assimp/matrix4x4.h>
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

namespace tnah 
{
	/**
	 * @class	AssimpGLMHelpers
	 *
	 * @brief	An assimp glm helpers class that converts Assimp matrices, vectors and quaternions into GLM
	 *
	 * @author	Dylan Blereau
	 * @date	12/09/2021
	 */

	class AssimpGLMHelpers 
	{
	public:

		/**
		 * @fn	static inline glm::mat4 AssimpGLMHelpers::ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
		 *
		 * @brief	Convert aiMatrix to glm format
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	from	Source for the.
		 *
		 * @returns	The matrix converted to glm format.
		 */

		static inline glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
		{
			glm::mat4 to;
			//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
			to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
			to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
			to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
			to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
			return to;
		}

		/**
		 * @fn	static inline glm::vec3 AssimpGLMHelpers::GetGLMVec(const aiVector3D& vec)
		 *
		 * @brief	Converts an aiVector3D to glm vec3 and returns
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vec	The vector.
		 *
		 * @returns	The glm vector.
		 */

		static inline glm::vec3 GetGLMVec(const aiVector3D& vec) 
		{
			return glm::vec3(vec.x, vec.y, vec.z);
		}

		/**
		 * @fn	static inline glm::quat AssimpGLMHelpers::GetGLMQuat(const aiQuaternion& pOrientation)
		 *
		 * @brief	Converts an aiQuaternion to glm::quat and returns
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	pOrientation	The orientation.
		 *
		 * @returns	The glm quaternion.
		 */

		static inline glm::quat GetGLMQuat(const aiQuaternion& pOrientation)
		{
			return glm::quat(pOrientation.w, pOrientation.x, pOrientation.y, pOrientation.z);
		}
	};
}
