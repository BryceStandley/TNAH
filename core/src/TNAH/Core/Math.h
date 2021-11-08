#pragma once
#define USE_MATH_DEFINES

#include <TNAH/Core/Core.h>
#pragma warning(push, 0)
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <corecrt_math_defines.h>
#include <IrrKlang/irrKlang.h>

#include "imgui.h"
#include "glm/glm.hpp"
#include "reactphysics3d/reactphysics3d.h"
#include "TNAH/Scene/Components/Components.h"
#pragma warning(pop)

namespace tnah {
	struct LogText
	{
		LogText(std::string s = "", glm::vec4 vec = glm::vec4(1)) : text(s), colour(vec)
		{}
		std::string text;
		glm::vec4 colour;
	};
	namespace Math {

		/**
		 * @fn	inline float BiLinearInterpolate(float a, float b, float blend)
		 *
		 * @brief	Bi linear interpolate
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	a	 	A float to process.
		 * @param 	b	 	A float to process.
		 * @param 	blend	The blend.
		 *
		 * @returns	A float.
		 */

		inline float BiLinearInterpolate(float a, float b, float blend)
		{
			double theta = blend * M_PI;
			float f = static_cast<float>(1.0f - cos(theta)) * 0.5f;
			return a * (1.0f - f) + b * f;
		}

		/**
		 * @fn	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
		 *
		 * @brief	Decompose transform
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 		  	transform  	The transform.
		 * @param [in,out]	translation	The translation.
		 * @param [in,out]	rotation   	The rotation.
		 * @param [in,out]	scale	   	The scale.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);

		/**
		 * @fn	inline bool CompareImGuiToGLM(const ImVec2& imgui, const glm::vec2& glm)
		 *
		 * @brief	Compare imgui vec2 to glm vec2
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	imgui	The imgui.
		 * @param 	glm  	The glm.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		inline bool CompareImGuiToGLM(const ImVec2& imgui, const glm::vec2& glm)
		{
			if(static_cast<int>(imgui.x) == static_cast<int>(glm.x) && static_cast<int>(imgui.y) == static_cast<int>(glm.y))
				return true;
			
			return false;
		}

		/**
		 * @fn	inline bool CompareImVec2(const ImVec2& a, const ImVec2 b)
		 *
		 * @brief	Compare imgui vec2
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	a	An ImVec2 to process.
		 * @param 	b	An ImVec2 to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		inline bool CompareImVec2(const ImVec2& a, const ImVec2 b)
		{
			if(static_cast<int>(a.x) == static_cast<int>(b.x) && static_cast<int>(a.y) == static_cast<int>(b.y))
				return true;
			
			return false;
		}

		/**
		 * @fn	static float Remap(float value, float oldMin, float oldMax, float newMin, float newMax)
		 *
		 * @brief	Remaps the range
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	value 	The value.
		 * @param 	oldMin	The old minimum.
		 * @param 	oldMax	The old maximum.
		 * @param 	newMin	The new minimum.
		 * @param 	newMax	The new maximum.
		 *
		 * @returns	A float.
		 */

		static float Remap(float value, float oldMin, float oldMax, float newMin, float newMax)
		{
			return newMin + (newMax - newMin) * ((value - oldMin) / (oldMax - oldMin));
		}

		/**
		 * @fn	irrklang::vec3df ConvertVec3ToVec3df(const glm::vec3& other);
		 *
		 * @brief	Convert glm vec3 to irrklang vec3df
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	other	The other.
		 *
		 * @returns	The vector converted 3 to vector 3df.
		 */

		irrklang::vec3df ConvertVec3ToVec3df(const glm::vec3& other);

		/**
		 * @fn	static rp3d::Vector3 ToRp3dVec3(const glm::vec3& values)
		 *
		 * @brief	Converts the glm vec3 values to a rp3D vector 3 values
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	values	The values.
		 *
		 * @returns	Values as a rp3d::Vector3.
		 */

		static rp3d::Vector3 ToRp3dVec3(const glm::vec3& values)
		{
			return rp3d::Vector3(values.x, values.y, values.z);
		}

		/**
		* @fn	static glm::vec3 FromRp3dVec3(const rp3d::Vector3& values)
		*
		* @brief	Converts the reactphysics3d vector3 values to a glm vec3 values
		*
		* @author	Bryce Standley
		* @date	7/09/2021
		*
		* @param 	values	The values.
		*
		* @returns	Values as a glm::vec3.
		*/

		static glm::vec3 FromRp3dVec3(const rp3d::Vector3& values)
		{
			return glm::vec3(values.x, values.y, values.z);
		}
		
		/**
		 * @fn	static rp3d::Quaternion ToRp3dQuat(const glm::quat& values)
		 *
		 * @brief	Converts the glm quaternion values to a rp3D quaternion
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	values	The values.
		 *
		 * @returns	Values as a rp3d::Quaternion.
		 */

		static rp3d::Quaternion ToRp3dQuat(const glm::quat& values)
		{
			return rp3d::Quaternion(values.x, values.y, values.z, values.w);
		}

		/**
		* @fn	static glm::quat FromRp3dQuat(const rp3d::Quaternion& values)
		*
		* @brief	Converts the Rp3d quaternion values to a glm quaternion
		*
		* @author	Bryce Standley
		* @date	7/09/2021
		*
		* @param 	values	The values.
		*
		* @returns	Values as a glm::quat
		*/

		static glm::quat FromRp3dQuat(const rp3d::Quaternion& values)
		{
			return glm::quat(values.w, values.x, values.y, values.z);
		}


		/**
		 * @fn	static rp3d::Transform ToRp3dTransform(const TransformComponent& transform)
		 *
		 * @brief	Converts a TranformComponent transform to a rp3d transform
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	transform	The transform.
		 *
		 * @returns	Transform as a rp3d::Transform.
		 */

		static rp3d::Transform ToRp3dTransform(const TransformComponent& transform)
		{
			return rp3d::Transform(ToRp3dVec3(transform.Position), ToRp3dQuat(glm::quat(transform.Rotation)));
		}

		/**
		 * @fn	static float Random()
		 *
		 * @brief	Gets the random
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	A float.
		 */

		static float Random()
		{
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			return r;
		}

		/**
		 * @fn	static float Random(const float& max)
		 *
		 * @brief	Randoms the given maximum
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	max	The maximum.
		 *
		 * @returns	A float.
		 */

		static float Random(const float& max)
		{
			float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/max));
			return r2;
		}

		/**
		 * @fn	static float Random(const float& min, const float& max)
		 *
		 * @brief	Randoms the min and max values
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	min	The minimum.
		 * @param 	max	The maximum.
		 *
		 * @returns	A float.
		 */

		static float Random(const float& min, const float& max)
		{
			float r3 = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
			return r3;
		}
	}

}