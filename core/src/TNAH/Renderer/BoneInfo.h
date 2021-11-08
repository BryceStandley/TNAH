#pragma once

/**
 * @struct	BoneInfo
 *
 * @brief	Information about the bone.
 *
 * @author	Dylan Blereau
 * @date	12/09/2021
 */

struct BoneInfo 
{
    
    /** @brief	The identifier */
    int id;

    /** @brief	Transform vertex from model space to bone space. */
    glm::mat4 offset;
};
