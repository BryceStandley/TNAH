#pragma once
#include <glm/glm.hpp>

namespace tnah
{
    /**
     * @struct	AABB
     *
     * @brief	An aabb bounding box
     *
     * @author	Bryce Standley
     * @date	7/09/2021
     */

    struct AABB
    {
        

        /** @brief	The minimum value and maximum value */
        glm::vec3 Min, Max;

        /**
         * @fn	AABB()
         *
         * @brief	Default constructor
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         */

        AABB()
            : Min(0.0f), Max(0.0f) {}

        /**
         * @fn	AABB(const glm::vec3& min, const glm::vec3& max)
         *
         * @brief	Constructor
         *
         * @author	Bryce Standley
         * @date	7/09/2021
         *
         * @param 	min	The minimum.
         * @param 	max	The maximum.
         */

        AABB(const glm::vec3& min, const glm::vec3& max)
            : Min(min), Max(max) {}

    };
}