#include <tnahpch.h>
#include "DirectionalLight.h"

namespace tnah {

    DirectionLight::DirectionLight()
        :Light(LightType::Directional)
    {
    }

    DirectionLight::DirectionLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse,
        const glm::vec3& specular)
    :Light(LightType::Directional)
    {
        SetUpLight(direction, ambient, diffuse, specular);
    }

    void DirectionLight::SetUpLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse,
        const glm::vec3& specular)
    {
        SetDirection(direction);
        SetAmbient(ambient);
        SetDiffuse(diffuse);
        SetSpecular(specular);
    }

}
