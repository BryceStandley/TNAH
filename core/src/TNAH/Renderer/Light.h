#pragma once
#include <TNAH/Core/Core.h>
#include <glm/glm.hpp>

#include "Shader.h"

namespace tnah {

    /**
     * @class	Light
     *
     * @brief	A light class that inherits from the refCounted class to allow the use of ref pointers. Responsible for lighting in applications
     *
     * @author	Bryce Standley
     * @date	12/09/2021
     */

    class Light : public RefCounted
    {
    public:

        /**
         * @enum	LightType
         *
         * @brief	Values that represent light types
         */

        enum class LightType
        {
            Directional = 0,
            Point = 1,
            Spot = 2
        };

        /**
         * @struct	ShaderLightInformation
         *
         * @brief	Information about the shader light.
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */

        struct ShaderLightInformation {

            /**
            * @brief	Shader light type, 0 = Directional, 1 = Point, 2 = Spot, Any other value = disabled
            * lightng in shader.
            */
            int type = 0;

            /** @brief	Camera View */
            glm::vec3 cameraPosition = glm::vec3(0.0f);
            

            /** @brief	The light position */
            glm::vec3 position = glm::vec3(0.0f);
            
            /** @brief	The light direction direction */
            glm::vec3 direction = glm::vec3(0.0f);
            

            /** @brief	The ambient lighting */
            glm::vec3 ambient = glm::vec3(0.0f);

            /** @brief	The diffuse lighting */
            glm::vec3 diffuse = glm::vec3(0.0f);

            /** @brief	The specular lighting */
            glm::vec3 specular = glm::vec3(0.0f);

            /** @brief	The color of the light */
            glm::vec3 color = glm::vec3(0.0f);

            /** @brief	The intensity */
            float intensity = 1.0f;

            /** @brief the constant */
            float constant = 0.0f;

            /** @brief	The linear */
            float linear = 0.0f;

            /** @brief	The quadratic */
            float quadratic = 0.0f;
           
            /** @brief	The cutoff for a spotlight */
            float cutoff = 0.0f;
        };

        /**
         * @fn	Light::Light(LightType type)
         *
         * @brief	Constructor
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	type	The type of light.
         */

        Light(LightType type) :m_Type(type) {}

        /**
         * @fn	virtual Light::~Light() = default;
         *
         * @brief	Defaulted destructor
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */

        virtual ~Light() = default;

        /**
         * @fn	static Ref<Light> Light::Create(LightType type);
         *
         * @brief	Creates a new light of the given type
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	type	The type of light.
         *
         * @returns	A Ref&lt;Light&gt;
         */

        static Ref<Light> Create(LightType type);

        /**
         * @fn	static Ref<Light> Light::CreateDirectional(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
         *
         * @brief	Creates a directional light
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	direction	The direction.
         * @param 	ambient  	The ambient.
         * @param 	diffuse  	The diffuse.
         * @param 	specular 	The specular.
         *
         * @returns	The new directional light.
         */

        static Ref<Light> CreateDirectional(const glm::vec3& direction, const glm::vec3& ambient,
            const glm::vec3& diffuse, const glm::vec3& specular);

        /**
         * @fn	static Ref<Light> Light::CreateDirectional();
         *
         * @brief	Creates the directional light
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The new directional light.
         */

        static Ref<Light> CreateDirectional();

        /**
         * @fn	static Ref<Light> Light::CreatePoint(const float& constant, const float& linear, const float& quadratic);
         *
         * @brief	Creates a point light
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	constant 	The constant.
         * @param 	linear   	The linear.
         * @param 	quadratic	The quadratic.
         *
         * @returns	The new point light.
         */

        static Ref<Light> CreatePoint(const float& constant, const float& linear, const float& quadratic);

        /**
         * @fn	static Ref<Light> Light::CreatePoint();
         *
         * @brief	Creates a point light
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The new point light.
         */

        static Ref<Light> CreatePoint();

        /**
         * @fn	static Ref<Light> Light::CreateSpot(const float& cutoff);
         *
         * @brief	Creates a spot light
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	cutoff	The cutoff.
         *
         * @returns	The new spot light.
         */

        static Ref<Light> CreateSpot(const float& cutoff);

        /**
         * @fn	static Ref<Light> Light::CreateSpot();
         *
         * @brief	Creates a spot light
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The new spot light.
         */

        static Ref<Light> CreateSpot();

        /**
         * @fn	virtual void Light::SetColor(const glm::vec4& value)
         *
         * @brief	Sets a color of the light
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetColor(const glm::vec4& value) { m_Color = value; }

        /**
         * @fn	virtual void Light::SetIntensity(const float& value)
         *
         * @brief	Sets light intensity
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetIntensity(const float& value) { m_Intensity = value; }

        /**
         * @fn	virtual void Light::SetPosition(const glm::vec3& value)
         *
         * @brief	Sets the light position
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetPosition(const glm::vec3& value) {m_Position = value; }

        /**
         * @fn	virtual void Light::SetType(const LightType& type)
         *
         * @brief	Sets the light type
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	type	The type.
         */

        virtual void SetType(const LightType& type) { m_Type = type; } 

        /**
         * @fn	virtual glm::vec4& Light::GetColor()
         *
         * @brief	Gets the color
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The color.
         */

        virtual glm::vec4& GetColor() { return m_Color; }

        /**
         * @fn	virtual float& Light::GetIntensity()
         *
         * @brief	Gets the intensity
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The intensity.
         */

        virtual float& GetIntensity() { return m_Intensity; }

        /**
         * @fn	virtual LightType& Light::GetType()
         *
         * @brief	Gets the type
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The type.
         */

        virtual LightType& GetType() { return m_Type; }

        /**
         * @fn	virtual glm::vec3& Light::GetPosition()
         *
         * @brief	Gets the position
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The position.
         */

        virtual glm::vec3& GetPosition() { return m_Position; }

        /**
         * @fn	ShaderLightInformation& Light::GetShaderInfo()
         *
         * @brief	Gets shader information
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The shader information.
         */

        ShaderLightInformation& GetShaderInfo() { return m_ShaderLightInformation; }

        /**
         * @fn	virtual void Light::SetDirection(const glm::vec3& value)
         *
         * @brief	Sets a direction
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetDirection(const glm::vec3& value) { m_Direction = value; }

        /**
         * @fn	virtual void Light::SetDiffuse(const glm::vec3& value)
         *
         * @brief	Sets a diffuse value
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetDiffuse(const glm::vec3& value) { m_Diffuse = value; }

        /**
         * @fn	virtual void Light::SetAmbient(const glm::vec3& value)
         *
         * @brief	Sets an ambient value
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetAmbient(const glm::vec3& value) { m_Ambient = value; }

        /**
         * @fn	virtual void Light::SetSpecular(const glm::vec3& value)
         *
         * @brief	Sets a specular value
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetSpecular(const glm::vec3& value) { m_Specular = value; }

        /**
         * @fn	virtual glm::vec3& Light::GetDirection()
         *
         * @brief	Gets the direction
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The direction.
         */

        virtual glm::vec3& GetDirection() { return m_Direction; }

        /**
         * @fn	virtual glm::vec3& Light::GetAmbient()
         *
         * @brief	Gets the ambient
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The ambient.
         */

        virtual glm::vec3& GetAmbient() { return m_Ambient; }

        /**
         * @fn	virtual glm::vec3& Light::GetDiffuse()
         *
         * @brief	Gets the diffuse
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The diffuse.
         */

        virtual glm::vec3& GetDiffuse() { return m_Diffuse; }

        /**
         * @fn	virtual glm::vec3& Light::GetSpecular()
         *
         * @brief	Gets the specular
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The specular.
         */

        virtual glm::vec3& GetSpecular() { return m_Specular;}

        /**
         * @fn	virtual void Light::SetConstant(const float& value)
         *
         * @brief	Sets a constant
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetConstant(const float& value) { m_Constant = value; }

        /**
         * @fn	virtual void Light::SetLinear(const float& value)
         *
         * @brief	Sets a linear
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetLinear(const float& value) { m_Linear = value; }

        /**
         * @fn	virtual void Light::SetQuadratic(const float& value)
         *
         * @brief	Sets a quadratic
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetQuadratic(const float& value) { m_Quadratic = value; }

        /**
         * @fn	virtual void Light::SetCutOff(const float& value)
         *
         * @brief	Sets cut off
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetCutOff(const float& value) { m_CutOff = glm::radians(value); }

        /**
         * @fn	virtual void Light::SetDistance(const int& value)
         *
         * @brief	Sets a distance
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	value	The value.
         */

        virtual void SetDistance(const int& value) { m_Distance = value; }

        /**
         * @fn	virtual float& Light::GetConstant()
         *
         * @brief	Gets the constant
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The constant.
         */

        virtual float& GetConstant()  { return m_Constant; }

        /**
         * @fn	virtual float& Light::GetLinear()
         *
         * @brief	Gets the linear
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The linear.
         */

        virtual float& GetLinear() { return m_Linear; }

        /**
         * @fn	virtual float& Light::GetQuadratic()
         *
         * @brief	Gets the quadratic
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The quadratic.
         */

        virtual float& GetQuadratic() { return m_Quadratic; }

        /**
         * @fn	virtual float Light::GetCutOff()
         *
         * @brief	Gets cut off
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The cut off.
         */

        virtual float GetCutOff() { return glm::degrees(m_CutOff); }

        /**
         * @fn	virtual int& Light::GetDistance()
         *
         * @brief	Gets the distance
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The distance.
         */

        virtual int& GetDistance() { return m_Distance; }

        /**
         * @fn	virtual void Light::UpdateShaderLightInfo(const glm::vec3& cameraPosition);
         *
         * @brief	Updates the shader light information described by cameraPosition
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	cameraPosition	The camera position.
         */

        virtual void UpdateShaderLightInfo(const glm::vec3& cameraPosition);

        /**
         * @fn	virtual void Light::CheckDistance(int distance);
         *
         * @brief	Check distance
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	distance	The distance.
         */

        virtual void CheckDistance(int distance);
    
    private:

        /**
         * @fn	inline std::string Light::GetTypeAsString()
         *
         * @brief	Gets type as string
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The type as string.
         */

        inline std::string GetTypeAsString()
        {
            switch (m_Type)
            {
                case LightType::Directional:
                    return std::string("Directional");
                case LightType::Point:
                    return std::string("Point");
                case LightType::Spot:
                    return std::string("Spot");
                default:
                    return std::string("Light");
            }
        }
        
        /** @brief	The direction */
        glm::vec3 m_Direction = glm::vec3(-0.2f, -1.0f, -0.3f);

        /** @brief	The ambient */
        glm::vec3 m_Ambient = glm::vec3(0.2f, 0.2f, 0.2f);

        /** @brief	The diffuse */
        glm::vec3 m_Diffuse = glm::vec3(0.5f, 0.5f, 0.5f);

        /** @brief	The specular */
        glm::vec3 m_Specular = glm::vec3(1.0f, 1.0f, 1.0f);
        
        /** @brief	The position */
        glm::vec3 m_Position = glm::vec3(0.0f);

        /** @brief	The color */
        glm::vec4 m_Color = glm::vec4(1.0f);

        /** @brief	The distance */
        int m_Distance = 7;

        /** @brief	The constant */
        float m_Constant = 1.0f;

        /** @brief	The linear */
        float m_Linear = 0.09f;

        /** @brief	The quadratic */
        float m_Quadratic = 0.032f;

        /** @brief	The cut off */
        float m_CutOff = glm::cos(glm::radians(12.5f));

        /** @brief	The intensity */
        float m_Intensity = 1.0f;

        /** @brief	The type */
        LightType m_Type = LightType::Directional;

        /** @brief	Information describing the shader light */
        ShaderLightInformation m_ShaderLightInformation = ShaderLightInformation();


        /** @brief	True if is scene light, false if not */
        bool m_IsSceneLight = false;

        friend class Scene;
        friend class Renderer;
        friend class EditorUI;
        friend class Serializer;
    
    };
}
