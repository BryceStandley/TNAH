#pragma once
#include "TNAH/Renderer/Light.h"

namespace tnah {
    /**
     * 
     * 
     * \brief Spot light type
     * 
     * \author Bryce Standley
     * \date 13/9/2021
     */
    class SpotLight : public Light
    {
    public:
        /**
         * 
         * \fn void SpotLight
         * 
         * \brief Constructor
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * 
         * 
         */
        SpotLight();

        /**
         * 
         * \fn void SpotLight
         * 
         * \brief Constructor
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param cutoff
         * 
         * 
         */
        SpotLight(const float& cutoff);

        /**
         * 
         * \fn void ~SpotLight
         * 
         * \brief Deconstructor
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * 
         * 
         */
        virtual ~SpotLight() {}

        /**
         * 
         * \fn void SetUpLight
         * 
         * \brief Light Set up
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param cutoff
         * 
         * 
         */
        void SetUpLight(const float& cutoff);
    };
}