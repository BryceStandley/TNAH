#pragma once
#include "TNAH/Core/Core.h"
#include <glm/glm.hpp>

#include "ComponentIdentification.h"
#include "TNAH/Renderer/RenderingBuffers.h"
#include "TNAH/Renderer/Material.h"
#include "TNAH/Renderer/VertexArray.h"
#include "TNAH/Renderer/Texture.h"


namespace tnah {

	/**********************************************************************************************//**
	 * @class	Skybox
	 *
	 * @brief	A skybox.
	 *
	 * @author	Bryce Standley, Dylan
	 * @date	10/09/2021
	 **************************************************************************************************/

	class Skybox {

	public:

		/**********************************************************************************************//**
		 * @fn	Skybox::Skybox();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Bryce Standley, Dylan
		 * @date	10/09/2021
		 **************************************************************************************************/

		Skybox();

		/**********************************************************************************************//**
		 * @fn	Skybox::Skybox(const Texture3DProperties& skyboxTextureProperties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley, Dylan
		 * @date	10/09/2021
		 *
		 * @param 	skyboxTextureProperties	The skybox texture properties.
		 **************************************************************************************************/

		Skybox(const Texture3DProperties& skyboxTextureProperties);

		/**********************************************************************************************//**
		 * @fn	float* Skybox::GetVBOData()
		 *
		 * @brief	Gets vbo data
		 *
		 * @author	Bryce Standley, Dylan
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else the vbo data.
		 **************************************************************************************************/

		float* GetVBOData() { return &m_VBOData[0]; }

		/**********************************************************************************************//**
		 * @fn	uint32_t Skybox::GetVBODataSize()
		 *
		 * @brief	Gets vbo data size
		 *
		 * @author	Bryce Standley, Dylan
		 * @date	10/09/2021
		 *
		 * @returns	The vbo data size.
		 **************************************************************************************************/

		uint32_t GetVBODataSize() { return m_VBOSize; }

		/**********************************************************************************************//**
		 * @fn	inline Ref<VertexArray> Skybox::GetVertexArray()
		 *
		 * @brief	Gets vertex array
		 *
		 * @author	Bryce Standley, Dylan
		 * @date	10/09/2021
		 *
		 * @returns	The vertex array.
		 **************************************************************************************************/

		inline Ref<VertexArray> GetVertexArray() { return m_VAO; }

		/**********************************************************************************************//**
		 * @fn	inline Ref<VertexBuffer> Skybox::GetVertexBuffer()
		 *
		 * @brief	Gets vertex buffer
		 *
		 * @author	Bryce Standley, Dylan
		 * @date	10/09/2021
		 *
		 * @returns	The vertex buffer.
		 **************************************************************************************************/

		inline Ref<VertexBuffer> GetVertexBuffer() { return m_VBO; }

		/**********************************************************************************************//**
		 * @fn	inline Ref<SkyboxMaterial> Skybox::GetMaterial()
		 *
		 * @brief	Gets the material
		 *
		 * @author	Bryce Standley, Dylan
		 * @date	10/09/2021
		 *
		 * @returns	The material.
		 **************************************************************************************************/

		inline Ref<SkyboxMaterial> GetMaterial() { return m_Material; }


	private:

		/**********************************************************************************************//**
		 * @fn	void Skybox::Create();
		 *
		 * @brief	Creates this object
		 *
		 * @author	Bryce Standley, Dylan
		 * @date	10/09/2021
		 **************************************************************************************************/

		void Create();
		/** @brief	The vao */
		Ref<VertexArray> m_VAO;
		/** @brief	The vbo */
		Ref<VertexBuffer> m_VBO;

		/** @brief	The buffer layout */
		VertexBufferLayout m_BufferLayout;
		
		/** @brief	The material */
		Ref<SkyboxMaterial> m_Material;
		/** @brief	The skybox texture */
		Ref<Texture3D> m_SkyboxTexture;
		
		/** @brief	Information describing the vbo */
		std::vector<float> m_VBOData;
		/** @brief	Size of the vbo */
		uint32_t m_VBOSize = 0;

	private:
		friend class Scene;
		friend class SkyboxComponent;
	};

	/**********************************************************************************************//**
	 * @class	SkyboxComponent
	 *
	 * @brief	A skybox component.
	 *
	 * @author	Bryce Standley, Dylan
	 * @date	10/09/2021
	 **************************************************************************************************/

	class SkyboxComponent
	{
	public:
		/** @brief	The scene skybox */
		Skybox* SceneSkybox;

		

		/**********************************************************************************************//**
		 * @fn	SkyboxComponent::SkyboxComponent()
		 *
		 * @brief	Default constructor
		 *
		 * @author	Bryce Standley, Dylan
		 * @date	10/09/2021
		 **************************************************************************************************/

		SkyboxComponent() 
		{
			SceneSkybox = new Skybox();
		}

		/**********************************************************************************************//**
		 * @fn	SkyboxComponent::SkyboxComponent(const SkyboxComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Bryce Standley, Dylan
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		SkyboxComponent(const SkyboxComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	SkyboxComponent::SkyboxComponent(const Texture3DProperties& cubemapProperties)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley, Dylan
		 * @date	10/09/2021
		 *
		 * @param 	cubemapProperties	The cubemap properties.
		 **************************************************************************************************/

		SkyboxComponent(const Texture3DProperties& cubemapProperties)
		{
			SceneSkybox = new Skybox(cubemapProperties);
		}

	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "skybox component";
		inline static ComponentTypes s_Types = {
			{ComponentVariations::Skybox},
{{ComponentCategory::Core, ComponentCategory::Rendering, ComponentCategory::Environment}}
		};
	};
}