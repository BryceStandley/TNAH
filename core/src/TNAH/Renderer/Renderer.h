#pragma once

#include "TNAH/Renderer/RenderCommand.h"

#include "TNAH/Scene/SceneCamera.h"
#include "TNAH/Scene/Components/Components.h"
#include "TNAH/Renderer/Material.h"
#include "Light.h"
#include "Mesh.h"
#include "Texture.h"

namespace tnah {

	/**
	 * @class	Renderer
	 *
	 * @brief	A renderer class responsible for the rendering of things such as meshes, terrain and skyboxes
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class Renderer
	{
	public:

		/**
		 * @fn	static void Renderer::Init();
		 *
		 * @brief	Initializes this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void Init();

		/**
		 * @fn	static void Renderer::Shutdown();
		 *
		 * @brief	Shuts down this object and frees any resources it is using
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void Shutdown();

		/**
		 * @fn	static void Renderer::OnWindowResize(uint32_t width, uint32_t height);
		 *
		 * @brief	Executes when the window is resized
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	width 	The width.
		 * @param 	height	The height.
		 */

		static void OnWindowResize(uint32_t width, uint32_t height);

		/**
		 * @fn	static void Renderer::BeginScene(SceneCamera& camera);
		 *
		 * @brief	Begins a scene
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	camera	The camera.
		 */
		static void BeginScene(SceneCamera& camera);

		/**
		 * @fn	static void Renderer::BeginScene(SceneCamera& camera, TransformComponent& cameraTransform);
		 *
		 * @brief	Begins a scene
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param [in,out]	camera		   	The camera.
		 * @param [in,out]	cameraTransform	The camera transform.
		 */

		static void BeginScene(SceneCamera& camera, TransformComponent& cameraTransform);

		/**
		 * @fn	static void Renderer::EndScene();
		 *
		 * @brief	Ends a scene
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void EndScene();

		/**
		 * @fn	static void Renderer::IncrementTextureSlot()
		 *
		 * @brief	Increment texture slot
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void IncrementTextureSlot() { s_CurrentTextureSlot++; }

		/**
		 * @fn	static uint32_t Renderer::GetCurrentTextureSlot()
		 *
		 * @brief	Gets current texture slot
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The current texture slot.
		 */

		static uint32_t GetCurrentTextureSlot() { return s_CurrentTextureSlot; }

		/**
		 * @fn	static uint32_t Renderer::GetAndIncrementTextureSlot()
		 *
		 * @brief	Gets and increment texture slot
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The and increment texture slot.
		 */

		static uint32_t GetAndIncrementTextureSlot() { s_CurrentTextureSlot++; return s_CurrentTextureSlot - 1; }


		/**
		 * @fn	static void Renderer::SetCullMode(const CullMode& mode);
		 *
		 * @brief	Sets cull mode
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	mode	The mode.
		 */

		static void SetCullMode(const CullMode& mode);

		/**
		 * @fn	static void Renderer::SetShaderLightInfo(Ref<Material> material, std::vector<Ref<Light>> lights);
		 *
		 * @brief	Sets shader light information
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	material	The material.
		 * @param 	lights  	The lights.
		 */
		static void SetShaderLightInfo(Ref<Material> material, std::vector<Ref<Light>> lights);

		/**
		 * @fn	static void Renderer::Submit(Ref<VertexArray> vertexArray, Ref<Shader> shader, const glm::mat4& transform = glm::mat4(1.0f));
		 *
		 * @brief	Submits to the renderer
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexArray	Array of vertices.
		 * @param 	shader	   	The shader.
		 * @param 	transform  	(Optional) The transform.
		 */

		static void Submit(Ref<VertexArray> vertexArray, Ref<Shader> shader, const glm::mat4& transform = glm::mat4(1.0f));

		/**
		 * @fn	static void Renderer::SubmitTerrain(Ref<VertexArray> vertexArray, Ref<Material> material, std::vector<Ref<Light>> sceneLights, const glm::mat4& transform = glm::mat4(1.0f));
		 *
		 * @brief	Submit terrain
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexArray	Array of vertices.
		 * @param 	material   	The material.
		 * @param 	sceneLights	The scene lights.
		 * @param 	transform  	(Optional) The transform.
		 */

		static void SubmitTerrain(Ref<VertexArray> vertexArray, Ref<Material> material, std::vector<Ref<Light>> sceneLights, const glm::mat4& transform = glm::mat4(1.0f));

		/**
		 * @fn	static void Renderer::SubmitMesh(Ref<VertexArray> vertexArray, Ref<Material> material, std::vector<Ref<Light>> sceneLights, const glm::mat4& transform = glm::mat4(1.0f), const bool& isAnimated = false, const std::vector<glm::mat4>& animTransforms = {glm::mat4(1.0f)});
		 *
		 * @brief	Submit mesh
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexArray   	Array of vertices.
		 * @param 	material	  	The material.
		 * @param 	sceneLights   	The scene lights.
		 * @param 	transform	  	(Optional) The transform.
		 * @param 	isAnimated	  	(Optional) True if is animated, false if not.
		 * @param 	animTransforms	(Optional) The animation transforms.
		 */

		static void SubmitMesh(Ref<VertexArray> vertexArray, Ref<Material> material, std::vector<Ref<Light>> sceneLights, const glm::mat4& transform = glm::mat4(1.0f), const bool& isAnimated = false, const std::vector<glm::mat4>& animTransforms = {glm::mat4(1.0f)});

		/**
		 * @fn	static void Renderer::SubmitSkybox(Ref<VertexArray> vertexArray, Ref<SkyboxMaterial> material);
		 *
		 * @brief	Submit skybox
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexArray	Array of vertices.
		 * @param 	material   	The material.
		 */

		static void SubmitSkybox(Ref<VertexArray> vertexArray, Ref<SkyboxMaterial> material);

		/**
		 * @fn	static void Renderer::SubmitCollider(Ref<VertexArray> lineVertexArray, Ref<VertexBuffer> lineVertexBuffer, Ref<VertexArray> triangleVertexArray, Ref<VertexBuffer> triangleVertexBuffer);
		 *
		 * @brief	Submit collider
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	lineVertexArray			Array of vertices.
		 * @param 	lineVertexBuffer		Buffer for line vertex data.
		 * @param 	triangleVertexArray 	Array of vertices.
		 * @param 	triangleVertexBuffer	Buffer for triangle vertex data.
		 */

		static void SubmitCollider(Ref<VertexArray> lineVertexArray, Ref<VertexBuffer> lineVertexBuffer, Ref<VertexArray> triangleVertexArray, Ref<VertexBuffer> triangleVertexBuffer);

		/**
		 * @fn	static RendererAPI::API Renderer::GetAPI()
		 *
		 * @brief	Gets the renderer API
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	the renderer API.
		 */

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		/**
		 * @fn	static Ref<Texture2D> Renderer::GetWhiteTexture();
		 *
		 * @brief	Gets white texture
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The white texture.
		 */

		static Ref<Texture2D> GetWhiteTexture();

		/**
		 * @fn	static Ref<Texture2D> Renderer::GetBlackTexture();
		 *
		 * @brief	Gets black texture
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The black texture.
		 */

		static Ref<Texture2D> GetBlackTexture();

		/**
		 * @fn	static Ref<Texture2D> Renderer::GetMissingTexture();
		 *
		 * @brief	Gets missing texture
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The missing texture.
		 */

		static Ref<Texture2D> GetMissingTexture();

		/**
		 * @fn	static std::vector<Ref<Texture2D>> Renderer::GetLoadedTextures();
		 *
		 * @brief	Gets loaded textures
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The loaded textures.
		 */

		static std::vector<Ref<Texture2D>> GetLoadedTextures();

		/**
		 * @fn	static std::vector<Ref<Shader>> Renderer::GetLoadedShaders();
		 *
		 * @brief	Gets loaded shaders
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The loaded shaders.
		 */

		static std::vector<Ref<Shader>> GetLoadedShaders();

		/**
		 * @fn	static void Renderer::RegisterTexture(Ref<Texture2D> texture);
		 *
		 * @brief	Registers the texture described by texture
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	texture	The texture.
		 */

		static void RegisterTexture(Ref<Texture2D> texture);

		/**
		 * @fn	static void Renderer::RegisterShader(Ref<Shader> shader);
		 *
		 * @brief	Registers the shader described by shader
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	shader	The shader.
		 */

		static void RegisterShader(Ref<Shader> shader);

		/**
		 * @fn	static std::vector<Ref<Model>> Renderer::GetLoadedModels();
		 *
		 * @brief	Gets loaded models
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The loaded models.
		 */

		static std::vector<Ref<Model>> GetLoadedModels();

		/**
		 * @fn	static void Renderer::RegisterModel(Ref<Model> model);
		 *
		 * @brief	Registers the model described by model
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	model	The model.
		 */

		static void RegisterModel(Ref<Model> model);

		/**
		 * @fn	static uint32_t Renderer::GetDrawCallsPerFrame();
		 *
		 * @brief	Gets draw calls per frame
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The draw calls per frame.
		 */

		static uint32_t GetDrawCallsPerFrame();

		/**
		 * @fn	static uint32_t Renderer::GetTotalLoadedTextures();
		 *
		 * @brief	Gets total loaded textures
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The total loaded textures.
		 */

		static uint32_t GetTotalLoadedTextures();

		/**
		 * @fn	static uint32_t Renderer::GetTotalLoadedShaders();
		 *
		 * @brief	Gets total loaded shaders
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The total loaded shaders.
		 */

		static uint32_t GetTotalLoadedShaders();

		/**
		 * @fn	static uint32_t Renderer::GetTotalLoadedModels();
		 *
		 * @brief	Gets total loaded models
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The total loaded models.
		 */

		static uint32_t GetTotalLoadedModels();


	
	private:

		/**
		 * @fn	static void Renderer::IncrementDrawCallsPerFrame();
		 *
		 * @brief	Increment draw calls per frame
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void IncrementDrawCallsPerFrame();

		/**
		 * @fn	static void Renderer::IncrementTotalLoadedTextures();
		 *
		 * @brief	Increment total loaded textures
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void IncrementTotalLoadedTextures();

		/**
		 * @fn	static void Renderer::IncrementTotalLoadedShaders();
		 *
		 * @brief	Increment total loaded shaders
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void IncrementTotalLoadedShaders();

		/**
		 * @fn	static void Renderer::IncrementTotalLoadedModels();
		 *
		 * @brief	Increment total loaded models
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void IncrementTotalLoadedModels();

		/**
		 * @fn	static void Renderer::ResetDrawCallsPerFrame();
		 *
		 * @brief	Resets the draw calls per frame
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void ResetDrawCallsPerFrame();

		/**
		 * @fn	static void Renderer::ResetTotalLoadedTextures();
		 *
		 * @brief	Resets the total loaded textures
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void ResetTotalLoadedTextures();

		/**
		 * @fn	static void Renderer::ResetTotalLoadedShaders();
		 *
		 * @brief	Resets the total loaded shaders
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void ResetTotalLoadedShaders();

		/**
		 * @fn	static void Renderer::ResetTotalLoadedModels();
		 *
		 * @brief	Resets the total loaded models
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		static void ResetTotalLoadedModels();

		/**
		 * @struct	SceneData
		 *
		 * @brief	scene data.
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		struct SceneData
		{

			/** @brief	The view */
			glm::mat4 View;

			/** @brief	The projection */
			glm::mat4 Projection;

			/** @brief	The view projection */
			glm::mat4 ViewProjection;

			/** @brief	The camera transform */
			TransformComponent CameraTransform;
		};



		/** @brief	The current texture slot */
		static uint32_t s_CurrentTextureSlot;

		/** @brief	Information describing the scene */
		static SceneData* s_SceneData;
		
	};
}
