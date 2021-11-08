#include "tnahpch.h"
#include "Renderer.h"

#include "Texture.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "TNAH/Core/Math.h"
#include "TNAH/Scene/Components/Components.h"

namespace tnah {

#pragma region RenderDataHolders
	struct RendererData
	{
		Ref<Texture2D> WhiteTexture;
		Ref<Texture2D> BlackTexture;
		Ref<Texture2D> MissingTexture;
		std::vector<Ref<Texture2D>> LoadedTextures;
		std::vector<Ref<Shader>> LoadedShaders;
		std::vector<Ref<Model>> LoadedModels;
	};

	struct RenderStats
	{
		uint32_t LoadedShaders;
		uint32_t LoadedTextures;
		uint32_t LoadedModels;
		uint32_t DrawCalls;
	};

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();
	uint32_t Renderer::s_CurrentTextureSlot = 1;
	static RenderStats* s_RenderStats = new RenderStats();
	static RendererData* s_Data = nullptr;
#pragma endregion 
	
#pragma region RendererStats
	uint32_t Renderer::GetDrawCallsPerFrame() { return s_RenderStats->DrawCalls; }
	uint32_t Renderer::GetTotalLoadedTextures() { return s_RenderStats->LoadedTextures; }
	uint32_t Renderer::GetTotalLoadedShaders() { return s_RenderStats->LoadedShaders; }
	uint32_t Renderer::GetTotalLoadedModels() { return s_RenderStats->LoadedModels; }

	void Renderer::IncrementDrawCallsPerFrame() { s_RenderStats->DrawCalls++; }
	void Renderer::IncrementTotalLoadedTextures() { s_RenderStats->LoadedTextures++; }
	void Renderer::IncrementTotalLoadedShaders() { s_RenderStats->LoadedShaders++; }
	void Renderer::IncrementTotalLoadedModels() { s_RenderStats->LoadedModels++; }

	void Renderer::ResetDrawCallsPerFrame() { s_RenderStats->DrawCalls = 0; }
	void Renderer::ResetTotalLoadedTextures() { s_RenderStats->LoadedTextures = 0; }
	void Renderer::ResetTotalLoadedShaders() { s_RenderStats->LoadedShaders = 0; }
	void Renderer::ResetTotalLoadedModels() { s_RenderStats->LoadedModels = 0; }
#pragma endregion 

#pragma region RendererInitAndShutdown
	void Renderer::Init()
	{
		s_Data = new RendererData();
		RenderCommand::Init();

		s_Data->WhiteTexture = (Texture2D::Create("Resources/textures/default/default_white.jpg"));
		s_Data->BlackTexture = (Texture2D::Create("Resources/textures/default/default_black.jpg"));
		s_Data->MissingTexture = (Texture2D::Create("Resources/textures/default/default_missing.jpg"));

		if (s_Data->WhiteTexture != nullptr)  RegisterTexture(s_Data->WhiteTexture);
		if (s_Data->BlackTexture != nullptr) RegisterTexture(s_Data->BlackTexture);
		if (s_Data->MissingTexture != nullptr) RegisterTexture(s_Data->MissingTexture);
		
	}

	void Renderer::Shutdown()
	{
		//Resetting all the loaded objects to shutdown
		for (auto t : s_Data->LoadedTextures)
		{
			t.Reset();
		}

		for (auto s : s_Data->LoadedShaders)
		{
			s.Reset();
		}

		for (auto m : s_Data->LoadedModels)
		{
			m.Reset();
		}

		delete[] s_Data;
	}
#pragma endregion

#pragma region Rendering
	
#pragma region StartAndEndScene
	void Renderer::BeginScene(SceneCamera& camera)
	{
		s_SceneData->View = camera.GetViewMatrix();
		s_SceneData->Projection = camera.GetProjectionMatrix();
		s_SceneData->ViewProjection = camera.GetViewProjectionMatrix();
		ResetDrawCallsPerFrame();
	}

	void Renderer::BeginScene(SceneCamera& camera, TransformComponent& cameraTransform)
	{
		s_SceneData->View = camera.GetViewMatrix();
		s_SceneData->Projection = camera.GetProjectionMatrix();
		s_SceneData->ViewProjection = camera.GetViewProjectionMatrix();
		s_SceneData->CameraTransform = cameraTransform;
		ResetDrawCallsPerFrame();
	}

	void Renderer::EndScene()
	{
	}
#pragma endregion

#pragma region LightSubmit
	
	void Renderer::SetShaderLightInfo(Ref<Material> material, std::vector<Ref<Light>> lights)
	{
		if(!material->GetShader()->IsBound()) material->BindShader();

		//The camera position is the same regardless of light so just take the first lights camera position value
		auto& l = lights[0]->GetShaderInfo();
		material->GetShader()->SetVec3("u_Global.cameraPosition", l.cameraPosition);

		uint32_t totalLights = 0;
		for(uint32_t i = 0; i < lights.size(); i++)
		{
			if(i > 8)
			{
				TNAH_INFO("The TNAH-Engine only supports 8 lights at once. Using the first 8 in the scene!");
				return;
			}
			
			auto& light = lights[i];
			auto& info = light->GetShaderInfo();
			if(light->m_IsSceneLight)
			{
				material->GetShader()->SetVec3("u_Global.direction", info.direction);
				material->GetShader()->SetVec3("u_Global.ambient", info.ambient);
				material->GetShader()->SetVec3("u_Global.diffuse", info.diffuse);
				material->GetShader()->SetVec3("u_Global.specular", info.specular);
				material->GetShader()->SetVec3("u_Global.color", info.color);
				material->GetShader()->SetFloat("u_Global.intensity", info.intensity);
			}
			else
			{
				material->GetShader()->SetInt("u_Light[" +std::to_string(totalLights) +"].type", info.type);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].position", info.position);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].direction", info.direction);
			
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].ambient", info.ambient);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].diffuse", info.diffuse);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].specular", info.specular);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].color", info.color);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(totalLights) +"].intensity", info.intensity);
			
				material->GetShader()->SetFloat("u_Light[" +std::to_string(totalLights) +"].constant", info.constant);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(totalLights) +"].linear", info.linear);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(totalLights) +"].quadratic", info.quadratic);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(totalLights) +"]cutoff", info.cutoff);
				totalLights++;
			}
			
			material->GetShader()->SetFloat("u_Material.shininess", material->GetProperties().Shininess);
			material->GetShader()->SetFloat("u_Material.metalness", material->GetProperties().Metalness);
		}
		material->GetShader()->SetInt("u_Global.totalLights", totalLights);

		///////
	}

#pragma endregion 

#pragma region RendererSubmits

#pragma region Submit
	
	void Renderer::Submit(Ref<VertexArray> vertexArray, Ref<Shader> shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		shader->SetMat4("u_Transform", transform);


		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		IncrementDrawCallsPerFrame();
	}

#pragma endregion 
	
#pragma region SkyboxRendering
	
	void Renderer::SubmitSkybox(Ref<VertexArray> vertexArray, Ref<SkyboxMaterial> material)
	{
		RenderCommand::SetDepthFunc(DepthFunc::Lequal);
		
		RenderCommand::SetDepthMask(false);
		
		RenderCommand::SetCullMode(CullMode::Back);
		material->BindShader();

		const glm::mat4 view = glm::mat4(glm::mat3(s_SceneData->View));
		
		material->GetShader()->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		material->GetShader()->SetVec3("u_CameraPosition", s_SceneData->CameraTransform.Position);
		
		material->BindTextures();
		
		vertexArray->Bind();
		
		RenderCommand::DrawArray(vertexArray);
		RenderCommand::SetDepthFunc(DepthFunc::Less);
		RenderCommand::SetDepthMask(true);
		RenderCommand::SetCullMode(CullMode::Front);
		IncrementDrawCallsPerFrame();
	}

#pragma endregion

#pragma region TerrainRendering
	void Renderer::SubmitTerrain(Ref<VertexArray> vertexArray, Ref<Material> material,
			std::vector<Ref<Light>> sceneLights, const glm::mat4& transform)
	{
		material->BindShader();
		material->GetShader()->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		material->GetShader()->SetMat4("u_Transform", transform);

		SetShaderLightInfo(material, sceneLights);

		material->BindTextures();
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		IncrementDrawCallsPerFrame();
	}
#pragma endregion

#pragma region MeshRendering
	void Renderer::SubmitMesh(Ref<VertexArray> vertexArray, Ref<Material> material,
			 std::vector<Ref<Light>> sceneLights, const glm::mat4& transform, const bool& isAnimated, const std::vector<glm::mat4>& animTransforms)
	{
		RenderCommand::SetCullMode(CullMode::Back);
		material->BindShader();
		material->GetShader()->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		material->GetShader()->SetMat4("u_Transform", transform);
		material->GetShader()->SetBool("u_Animated", isAnimated);

		if(isAnimated)
		{
			for(uint32_t i = 0; i < animTransforms.size(); ++i)
			{
				std::string name = "u_FinalBonesMatrices[" + std::to_string(i) + "]";
				material->GetShader()->SetMat4(name.c_str(), animTransforms[i]);
			}
		}

		SetShaderLightInfo(material, sceneLights);
		
		material->BindTextures();
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		RenderCommand::SetCullMode(CullMode::Front);
		IncrementDrawCallsPerFrame();
	}
#pragma endregion

#pragma region PhysicsColliderRendering
	
	void Renderer::SubmitCollider(Ref<VertexArray> lineVertexArray, Ref<VertexBuffer> lineVertexBuffer,
		Ref<VertexArray> triangleVertexArray, Ref<VertexBuffer> triangleVertexBuffer)
	{
		RenderCommand::SetWireframe(true);
		auto shader = Physics::PhysicsEngine::GetColliderShader();
		shader->Bind();
		shader->SetMat4("u_ViewProjectionMatrix", s_SceneData->ViewProjection);
		shader->SetMat4("u_Transform",  Physics::PhysicsEngine::GetColliderRendererTransform().GetTransform());
		shader->SetInt("u_isGlobalVertexColorEnabled", 0); // use global color
		shader->SetVec4("u_GlobalVertexColor", glm::vec4(1.0f)); // Disable global color
		
		
		const auto renderer = Physics::PhysicsEngine::GetColliderRenderer();
		
		if(renderer->getNbLines() > 0)
		{
			lineVertexArray->UpdateVertexBuffer();
			RenderCommand::DrawArray(lineVertexArray, DrawMode::Lines);
		}
		
		if(renderer->getNbTriangles() > 0)
		{
			triangleVertexArray->UpdateVertexBuffer();
			RenderCommand::DrawArray(triangleVertexArray, DrawMode::Triangles);
		}

		shader->Unbind();
		RenderCommand::SetWireframe(false);
	}
#pragma endregion
	
#pragma endregion
	
#pragma endregion 
	
#pragma region ResourceManagement
	
	Ref<Texture2D> Renderer::GetWhiteTexture()
	{
		return s_Data->WhiteTexture;
	}

	Ref<Texture2D> Renderer::GetBlackTexture()
	{
		return s_Data->BlackTexture;
	}

	Ref<Texture2D> Renderer::GetMissingTexture()
	{
		return s_Data->MissingTexture;
	}

	std::vector<Ref<Texture2D>> Renderer::GetLoadedTextures()
	{
		return s_Data->LoadedTextures;
	}

	std::vector<Ref<Shader>> Renderer::GetLoadedShaders()
	{
		return s_Data->LoadedShaders;
	}

	void Renderer::RegisterTexture(Ref<Texture2D> texture)
	{
		s_Data->LoadedTextures.push_back(texture);
		IncrementTotalLoadedTextures();
	}

	void Renderer::RegisterShader(Ref<Shader> shader)
	{
		s_Data->LoadedShaders.push_back(shader);
		IncrementTotalLoadedShaders();
	}

	std::vector<Ref<Model>> Renderer::GetLoadedModels()
	{
		return s_Data->LoadedModels;
	}

	void Renderer::RegisterModel(Ref<Model> model)
	{
		s_Data->LoadedModels.push_back(model);
		IncrementTotalLoadedModels();
	}
#pragma endregion 

}
