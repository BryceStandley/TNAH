#pragma once
#include "TNAH/Renderer/Light.h"

namespace tnah {
    
    
    class DirectionLight : public Light
    {
    public:

        /**
         * 
         * \fn void DirectionLight
         * 
         * \brief Default constructor
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * 
         * 
         */
        DirectionLight();

        /**
         * 
         * \fn void DirectionLight
         * 
         * \brief Constructor of the light
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param direction Light Direction
         * \param ambient Light ambient
         * \param diffuse Light diffuse
         * \param specular Light specular
         * 
         * 
         */
        DirectionLight(const glm::vec3& direction, const glm::vec3& ambient,const glm::vec3& diffuse,const glm::vec3& specular);

        /**
         * 
         * \fn void ~DirectionLight
         * 
         * \brief Default deconstructor
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * 
         * 
         */
        virtual ~DirectionLight() {}


        /**
         * 
         * \fn void SetUpLight
         * 
         * \brief Sets up the light with given inputs.
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param direction Light Direction
         * \param ambient Light ambient
         * \param diffuse Light diffuse
         * \param specular Light specular
         * 
         * 
         */
        void SetUpLight(const glm::vec3& direction, const glm::vec3& ambient,const glm::vec3& diffuse,const glm::vec3& specular);
    };
}