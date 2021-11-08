#include "tnahpch.h"
#include "PointLight.h"

namespace tnah {
    PointLight::PointLight()
        :Light(LightType::Point)
    {
    }

    PointLight::PointLight(const float& constant, const float& linear, const float& quadratic)
        :Light(LightType::Point)
    {
        SetUpLight(constant, linear, quadratic);
    }

    void PointLight::SetUpLight(const float& constant, const float& linear, const float& quadratic)
    {
        SetConstant(constant);
        SetLinear(linear);
        SetQuadratic(quadratic);
    }
}
