#pragma once

#include "TNAH/core/Core.h"

#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Texture.h"


namespace tnah
{
	/**
	 * @struct	MaterialProperties
	 *
	 * @brief	A material properties struct.
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	struct MaterialProperties
	{

		/** @brief	The shininess */
		float Shininess = 32.0f;

		/** @brief	The metalness */
		float Metalness = 0.0f;

		/**
		 * @fn	MaterialProperties() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		MaterialProperties() = default;

		/**
		 * @fn	MaterialProperties(float shine, float metal)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shine	The shine.
		 * @param 	metal	The metal.
		 */

		MaterialProperties(float shine, float metal)
			:Shininess(shine), Metalness(metal) {}
	};
	
	
	class Material : public RefCounted
	{
	public:

		/**
		 * @fn	static Ref<Material> Material::Create(const Ref<Shader>& shader);
		 *
		 * @brief	Creates a new material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader	The shader.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<Material> Create(const Ref<Shader>& shader);

		/**
		 * @fn	static Ref<Material> Material::Create(const Ref<Shader>& shader, const MaterialProperties& properties);
		 *
		 * @brief	Creates a new material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader	  	The shader.
		 * @param 	properties	The properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<Material> Create(const Ref<Shader>& shader, const MaterialProperties& properties);

		/**
		 * @fn	static Ref<Material> Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		 *
		 * @brief	Creates a new material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<Material> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		/**
		 * @fn	static Ref<Material> Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		 *
		 * @brief	Creates a new material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<Material> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);

		/**
		 * @fn	static Ref<Material> Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		 *
		 * @brief	Creates a new material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	shininess		  	The shininess.
		 * @param 	metalness		  	The metalness.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<Material> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);

		/**
		 * @fn	void Material::SetTextures(std::vector<Ref<Texture2D>> textures);
		 *
		 * @brief	Sets the textures
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	textures	The textures.
		 */

		void SetTextures(std::vector<Ref<Texture2D>> textures);

		/**
		 * @fn void Material::AddTexture(Ref<Texture2D> texture)
		 *
		 * @brief Adds a texture to the material.
		 *
		 *  @author Bryce Standley
		 *  @date 27/10/2021
		 *
		 *  @param texture The texture to add.
		 *
		 */
		void AddTexture(Ref<Texture2D> texture) { m_Textures.push_back(texture); }

		/**
		 * @fn	virtual void Material::BindTextures();
		 *
		 * @brief	Bind textures
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void BindTextures();

		/**
		 * @fn	virtual void Material::BindShader();
		 *
		 * @brief	Bind shader
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void BindShader();

		/**
		 * @fn	virtual void Material::UnBindShader();
		 *
		 * @brief	Unbind shader
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void UnBindShader();

		/**
		 * @fn	virtual Ref<Shader> Material::GetShader() const
		 *
		 * @brief	Gets the shader
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The shader.
		 */

		virtual Ref<Shader> GetShader() const { return m_Shader; }

		/**
		 * @fn	std::vector<Ref<Texture2D>> Material::GetTextures() const
		 *
		 * @brief	Gets the textures
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The textures.
		 */

		std::vector<Ref<Texture2D>> GetTextures() const { return m_Textures; }

		/**
		 * @fn	virtual MaterialProperties& Material::GetProperties()
		 *
		 * @brief	Gets the properties
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The properties.
		 */

		virtual MaterialProperties& GetProperties() { return m_Properties; }

		/**
		 * @fn	virtual Material::~Material();
		 *
		 * @brief	Destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~Material();

		/**
		 * @fn	Material::Material();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		Material();

		/**
		 * @fn	Material::Material(const Ref<Shader>& shader);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader	The shader.
		 */

		Material(const Ref<Shader>& shader);

		/**
		 * @fn	Material::Material(const Ref<Shader>& shader, const MaterialProperties& properties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader	  	The shader.
		 * @param 	properties	The properties.
		 */

		Material(const Ref<Shader>& shader, const MaterialProperties& properties);

		/**
		 * @fn	Material::Material(const MaterialProperties& properties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	properties	The properties.
		 */

		Material(const MaterialProperties& properties);

		/**
		 * @fn	Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 */

		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		/**
		 * @fn	Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 */

		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);

		/**
		 * @fn	Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	shininess		  	The shininess.
		 * @param 	metalness		  	The metalness.
		 */

		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
	
	protected:

		/** @brief	The shader */
		Ref<Shader> m_Shader;

		/** @brief	The properties */
		MaterialProperties m_Properties;
	
	private:

		/** @brief	The textures */
		std::vector<Ref<Texture2D>> m_Textures;

		friend class EditorUI;
		
	};

	/**
	 * @class	SkyboxMaterial
	 *
	 * @brief	A skybox material class that inherits from the material class
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class SkyboxMaterial : public Material
	{
	public:

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader	The shader.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader			 	The shader.
		 * @param 	cubemapProperties	The cubemap properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader, const MaterialProperties& properties);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader	  	The shader.
		 * @param 	properties	The properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader, const MaterialProperties& properties);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader			 	The shader.
		 * @param 	properties		 	The properties.
		 * @param 	cubemapProperties	The cubemap properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 * @param 	cubemapProperties 	The cubemap properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	shininess		  	The shininess.
		 * @param 	metalness		  	The metalness.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);

		/**
		 * @fn	void SkyboxMaterial::BindTextures() override;
		 *
		 * @brief	Bind textures
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		void BindTextures() override;

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader	The shader.
		 */

		SkyboxMaterial(const Ref<Shader>& shader);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader			 	The shader.
		 * @param 	cubemapProperties	The cubemap properties.
		 */

		SkyboxMaterial(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader	  	The shader.
		 * @param 	properties	The properties.
		 */

		SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader			 	The shader.
		 * @param 	properties		 	The properties.
		 * @param 	cubemapProperties	The cubemap properties.
		 */

		SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 */

		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 */

		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 * @param 	cubemapProperties 	The cubemap properties.
		 */

		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	shininess		  	The shininess.
		 * @param 	metalness		  	The metalness.
		 */

		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);

		/**
		 * @fn	Ref<Texture3D> SkyboxMaterial::GetCubemapTextures() const
		 *
		 * @brief	Gets cubemap textures
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The cubemap textures.
		 */

		Ref<Texture3D> GetCubemapTextures() const { return m_Cubemap; }

		/**
		 * @fn	Texture3DProperties SkyboxMaterial::GetCubemapProperties() const
		 *
		 * @brief	Gets cubemap properties
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The cubemap properties.
		 */

		Texture3DProperties GetCubemapProperties() const { return m_CubemapProperties; }

		/**
		 * @fn	SkyboxMaterial::~SkyboxMaterial() override;
		 *
		 * @brief	Destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		~SkyboxMaterial() override;

	private:
		
		/** @brief	The cubemap properties */
		Texture3DProperties m_CubemapProperties;

		/** @brief	The cubemap */
		Ref<Texture3D> m_Cubemap;
	};

}
