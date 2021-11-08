#include "tnahpch.h"
#include "SpotLight.h"

namespace tnah {


    SpotLight::SpotLight()
        :Light(LightType::Spot)
    {
    }

    SpotLight::SpotLight(const float& cutoff)
        :Light(LightType::Spot)
    {
    }

    void SpotLight::SetUpLight(const float& cutoff)
    {
        SetCutOff(cutoff);
    }
}
