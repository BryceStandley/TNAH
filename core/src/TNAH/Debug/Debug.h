#pragma once

/**
 * @namespace tnah::Debug {}
 *
 * @brief Debug Sub-namespace
 */
namespace tnah::Debug{

	
		/**
		 * @brief Debugs info as core info of a vec3 with a message
		 * @author Bryce Standley
		 * @date 07-11-2021
		 */
		static void CoreInfo(const glm::vec3& value, const std::string& message = "")
		{
			TNAH_CORE_INFO("(Debug): {0}: X({1}) - Y({2}) - Z({3})",message, value.x, value.y, value.z);
		}

		/**
		 * @brief Debugs info as core info of a quaternion with a message
		 * @author Bryce Standley
		 * @date 07-11-2021
		 */
		static void CoreInfo(const glm::quat& val, const std::string& message = "")
		{
			TNAH_CORE_INFO("(Debug): {0}: X({1}) - Y({2}) - Z({3}) - W({4})",message, val.x, val.y, val.z, val.w);
		}

		/**
		 * @brief Debugs info as core info of a vec3
		 * @author Bryce Standley
		 * @date 07-11-2021
		 */
		static void CoreInfo(const glm::vec3& value)
		{
			TNAH_CORE_INFO("(Debug): X({0}) - Y({1}) - Z({2})", value.x, value.y, value.z);
		}

		/**
		 * @brief Debugs warning as core info of a vec3
		 * @author Bryce Standley
		 * @date 07-11-2021
		 */
		static void CoreWarm(const glm::vec3& value)
		{
			TNAH_CORE_WARN("(Debug): X({0}) - Y({1}) - Z({2})", value.x, value.y, value.z);
		}

		/**
		 * @brief Debugs error as core info of a vec3
		 * @author Bryce Standley
		 * @date 07-11-2021
		 */
		static void CoreError(const glm::vec3& value)
		{
			TNAH_CORE_ERROR("(Debug): X({0}) - Y({1}) - Z({2})", value.x, value.y, value.z);
		}

	
}