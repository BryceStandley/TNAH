#include <tnahpch.h>
#include "Scene.h"
#include "GameObject.h"
#include "Components/Components.h"
#include "TNAH/Core/Application.h"
#include "TNAH/Core/Input.h"
#include "TNAH/Renderer/Renderer.h"
#include "TNAH/Audio/Audio.h"
#include "TNAH/Physics/PhysicsEvents.h"
#include <glm/gtx/string_cast.hpp>

#include "Components/AI/Affordance.h"
#include "Components/AI/AIComponent.h"
#include "Components/AI/CharacterComponent.h"
#include "Components/AI/PlayerInteractions.h"

namespace tnah{

#pragma region SceneSetups
	
	Scene::ActiveScene Scene::s_ActiveScene = Scene::ActiveScene();

	struct SceneComponent
	{
		UUID SceneID;
	};
	
	std::map<UUID, GameObject>& Scene::GetGameObjectsInScene()
	{
		return m_GameObjectsInScene;
	}

	GameObject* Scene::GetRefGameObject(const UUID& id)
	{
		return &m_GameObjectsInScene[id];
	}

	Scene::Scene(bool editor)
	{
		m_SceneEntity = m_Registry.create();
		m_Registry.emplace<SceneComponent>(m_SceneEntity, m_SceneID);
		if(editor)
		{
			m_EditorCamera = CreateEditorCamera().GetUUID();
			FramebufferSpecification fbspec = {1280, 720};
			m_EditorSceneFramebuffer = Framebuffer::Create(fbspec);
			m_EditorGameFramebuffer = Framebuffer::Create(fbspec);
			m_IsEditorScene = true;
			m_RenderPasses = 2;
		}

		auto& cam = CreateGameObject("Main Camera");
		m_ActiveCamera = cam.GetUUID();
		auto& camera = cam.AddComponent<CameraComponent>();
		Camera::SetMainCamera(camera.Camera);
		cam.AddComponent<SkyboxComponent>();
		
		
		auto& l = CreateGameObject("Main Light");
		m_SceneLight = l.GetUUID();
		auto& light = l.AddComponent<LightComponent>();
		light.Light = Light::CreateDirectional();
		light.Light->m_IsSceneLight = true;

		//Physics
		listener = new Physics::PhysicsEvents();
		Physics::PhysicsEngine::Initialise(listener);
		
		s_ActiveScene.Scene.Reset(this);
	}

	Scene::~Scene()
	{
		m_Registry.clear();
		m_GameObjectsInScene.clear();
		//s_ActiveScenes.erase(m_SceneID);
		m_EditorGameFramebuffer.Reset();
		m_EditorSceneFramebuffer.Reset();

	}

	void Scene::ClearActiveScene()
	{
		s_ActiveScene.Scene.Reset();
	}

	Ref<Scene> Scene::CreateNewEditorScene()
	{
		return Ref<Scene>::Create(true);
	}

	GameObject& Scene::GetEditorCamera()
	{
		return m_GameObjectsInScene[m_EditorCamera];
	}

	Ref<Scene> Scene::CreateEmptyScene()
	{
		return Ref<Scene>::Create();
	}

#pragma endregion SceneSetups

#pragma region SceneUpdate
	
	void Scene::OnUpdate(Timestep deltaTime)
	{
		
#pragma region OnUpdates
		
		Physics::PhysicsEngine::OnUpdate(deltaTime);

#pragma endregion OnUpdates
		
#pragma region PlayerControllerUpdate
		//TODO: Actually test the player controller component
		// Process any PlayerControllers before updating anything else in the scene
		{
			auto e = EditorComponent();

			Audio::OnUpdate();
			
			auto view = m_Registry.view<PlayerControllerComponent, TransformComponent>();
			for(auto obj : view)
			{
				auto& editor = m_GameObjectsInScene[m_EditorCamera].GetComponent<EditorComponent>();
				//Only run this update for a player controller if the editor isnt empty, were in play mode to test the scene
				// or this scene isnt being ran in a editor ie in the runtime
				if((editor.m_EditorMode == EditorComponent::EditorMode::Play) || (!m_IsEditorScene && this->FindGameObjectByID(obj).IsActive()))
				{
					auto& transform = view.get<TransformComponent>(obj);
					auto& player = view.get<PlayerControllerComponent>(obj);
					// Only continue if the component is active/enabled
					if(player.IsActive())
					{
						if(!player.m_MouseDisabled) Application::Get().GetWindow().SetCursorDisabled(true); player.m_MouseDisabled = true;
						float s = 0.0f;
						// if were sprinting, use sprint speed else if were crouched use crouched speed else use the normal movement speed
						auto speed = (player.IsSprinting()) ? player.SprintSpeed : (s = (player.IsCrouched()) ? player.CrouchSpeed : player.MovementSpeed);
				
						if(Input::IsKeyPressed(player.Forward)) transform.Position += transform.Forward * speed * deltaTime.GetSeconds();
						if(Input::IsKeyPressed(player.Backward)) transform.Position -= transform.Forward * speed * deltaTime.GetSeconds();
						if(Input::IsKeyPressed(player.Left)) transform.Position -= transform.Right * speed * deltaTime.GetSeconds();
						if(Input::IsKeyPressed(player.Right)) transform.Position += transform.Right * speed * deltaTime.GetSeconds();
						player.ProcessMouseRotation(transform);
					}
				}
			}
			
		}
#pragma endregion

#pragma region TransformComponentUpdate
		
		//Update all transform components and their forward, right and up vectors
		{
			auto view = m_Registry.view<TransformComponent>();
			for (auto obj : view)
			{
				auto& transform = view.get<TransformComponent>(obj);

				glm::vec3 forward = glm::vec3(0.0f);
				glm::vec3 right = glm::vec3(0.0f);
				glm::vec3 up = glm::vec3(0.0f);
				forward.x = cos(glm::radians(transform.Rotation.x)) * cos(glm::radians(transform.Rotation.y));
				forward.y = sin(glm::radians(transform.Rotation.y));
				forward.z = sin(glm::radians(transform.Rotation.x)) * cos(glm::radians(transform.Rotation.y));
				forward = glm::normalize(forward);
				right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
				up = glm::normalize(glm::cross(right, forward));
				transform.Forward = forward;
				transform.Right = right;
				transform.Up = up;
			}
		}

		{
			auto view = m_Registry.view<AStarObstacleComponent, TransformComponent>();
			{
				for(auto entity : view)
				{
					auto & star = view.get<AStarObstacleComponent>(entity);
					auto& transform = view.get<TransformComponent>(entity);
					AStar::AddUsedPosition(Int2(static_cast<int>(round(transform.Position.x)), static_cast<int>(round(transform.Position.z))), star.dynamic);
				}
			}
		}
		
#pragma endregion	
		
#pragma region FramebufferBindings
		uint32_t passes = 0;
		do
		{
			if(m_IsEditorScene)
			{
				if(passes == 0)
				{
					m_EditorSceneFramebuffer->Bind(0);
				}
				
				if(passes == 1)
				{
					
					m_EditorGameFramebuffer->Bind(0);
				}
			}
		
			//after the transform is updated, update the camera matrix etc 
			{
				if(m_IsEditorScene && passes == 0)
				{
					auto& camera = GetEditorCamera().GetComponent<EditorCameraComponent>().EditorCamera;
					auto& transform = GetEditorCamera().Transform();
					camera.OnUpdate(transform);
				}
				else
				{
					auto view = m_Registry.view<TransformComponent, CameraComponent>();
					for(auto entity : view)
					{ 
						auto& camera = view.get<CameraComponent>(entity);
						auto& transform = view.get<TransformComponent>(entity);
						camera.Camera.OnUpdate(transform);
					}
				}
			}
#pragma endregion 			

#pragma region Rendering
			{
#pragma region ClearColorAndSkybox
				glm::vec3 cameraPosition;
				bool usingSkybox = false;
				{
					//Check if its were in the editor, if so render from the perspective of the editor camera
					if(m_IsEditorScene && passes == 0)
					{
						auto& camera = GetEditorCamera().GetComponent<EditorCameraComponent>();
						auto& transform = GetEditorCamera().Transform();
						cameraPosition = transform.Position;
						if(camera.ClearMode == CameraClearMode::Color)
						{
							RenderCommand::SetClearColor(camera.ClearColor);
							RenderCommand::Clear();
						
						}
						else if(camera.ClearMode == CameraClearMode::Skybox)
						{
							RenderCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});
							RenderCommand::Clear();
							usingSkybox = true;
						}
					
						Renderer::BeginScene(camera, transform);
					
					}
					else
					{
						auto view = m_Registry.view<TransformComponent, CameraComponent>();
						for(auto entity : view)
						{ 
							auto& camera = view.get<CameraComponent>(entity);
							auto& transform = view.get<TransformComponent>(entity);
							cameraPosition = transform.Position;
							if(camera.ClearMode == CameraClearMode::Color)
							{
								RenderCommand::SetClearColor(camera.ClearColor);
								RenderCommand::Clear();
							}
							else if(camera.ClearMode == CameraClearMode::Skybox)
							{
								RenderCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});
								RenderCommand::Clear();
								usingSkybox = true;
							}
						
							Renderer::BeginScene(camera, transform);
							break;
							TNAH_CORE_ASSERT(false, "The TNAH-Engine only supports rendering from a single camera!")
						}
					}
				}

				// Skybox
				if(usingSkybox)
				{
					auto view = m_Registry.view<SkyboxComponent>();
					for(auto obj : view)
					{
						auto& skybox = view.get<SkyboxComponent>(obj);
						// Bind the skybox shader
						// Do any skybox render setup
						Renderer::SubmitSkybox(skybox.SceneSkybox->GetVertexArray(), skybox.SceneSkybox->GetMaterial());
					}
				}
#pragma endregion 
				
#pragma region Lighting
				std::vector<Ref<Light>> sceneLights;
				{
					auto view = m_Registry.view<LightComponent, TransformComponent>();
					for(auto entity : view)
					{
						auto& light = view.get<LightComponent>(entity);
						auto& transform = view.get<TransformComponent>(entity);
						if(light.Light == nullptr) continue; 
						light.Light->SetPosition(transform.Position);
						light.Light->UpdateShaderLightInfo(cameraPosition);
						sceneLights.push_back(light.Light);
					}
				}
#pragma endregion

#pragma region TerrainRender
				//Render any terrain objects
				{
					auto view = m_Registry.view<TransformComponent, TerrainComponent>();
					for(auto entity : view)
					{
						auto& terrain = view.get<TerrainComponent>(entity);
						auto& transform = view.get<TransformComponent>(entity);

						Renderer::SubmitTerrain(terrain.SceneTerrain->GetVertexArray(), terrain.SceneTerrain->GetMaterial(), sceneLights, transform.GetTransform());
					}
				}
#pragma endregion

#pragma region MeshRender
				//Render all mesh components
				{
					auto view = m_Registry.view<TransformComponent, MeshComponent>();
					for(auto entity : view)
					{
						auto& model = view.get<MeshComponent>(entity);
						auto& transform = view.get<TransformComponent>(entity);
						glm::mat4 matrix = transform.GetTransform();
						auto& go = FindGameObjectByID(entity);
						if(go.HasComponent<RigidBodyComponent>())
						{
							auto & rb = go.GetComponent<RigidBodyComponent>();
							if(rb.Body->GetType() == Physics::BodyType::Dynamic)
								matrix = transform.GetQuatTransform();
						}
						
						if(model.Model)
						{
							for (auto& mesh : model.Model->GetMeshes())
							{
								if(mesh.GetMeshMaterial()->GetTextures().size() == 1)
								{
									//theres no specular texture on the mesh. assign the default black to the specular.
									auto mat = mesh.GetMeshMaterial();
									auto t = Renderer::GetBlackTexture(); // we want to copy not directly use to be able to set a custom uniform name
									t->m_UniformName = "texture_specular1";
									mat->AddTexture(t);
									
								}
								Renderer::SubmitMesh(mesh.GetMeshVertexArray(), mesh.GetMeshMaterial(), sceneLights, matrix);
							}
						}
					}
				}
#pragma endregion

#pragma region ColliderRender

				{
					
					//Collider rendering should only be used for debugging and in the editor to set sizes
					if((m_IsEditorScene || Application::Get().GetDebugModeStatus()) && Physics::PhysicsEngine::IsColliderRenderingEnabled() && passes == 0)
					{
						auto pair = Physics::PhysicsEngine::GetColliderRenderObjects();
						auto lineArr = pair.first.first;
						auto lineBuf = pair.first.second;
				
						auto triArr = pair.second.first;
						auto triBuf = pair.second.second;
						Renderer::SubmitCollider(lineArr, lineBuf,triArr,triBuf);
					}
				}

				{

						auto view = m_Registry.view<AStarComponent, MeshComponent, TransformComponent>();
						{
							for(auto entity : view)
							{
								auto &astar = view.get<AStarComponent>(entity);
								if(astar.reset)
								{
									AStar::Init(astar.StartingPos, astar.Size);
									astar.reset = false;
								}
								
								if(Application::Get().GetDebugModeStatus() || astar.DisplayMap)
								{
								auto& model = view.get<MeshComponent>(entity);
								auto& transform = view.get<TransformComponent>(entity);
							
								auto map = AStar::GetUsedPoints();
								//auto array = AStar::GetMapPoints();
								auto pos = AStar::GetStartingPos();
								auto end = AStar::GetEndPosition();
								for(int x = pos.x; x < end.x; x++)
								{
									for(int y = pos.y; y < end.y; y++)
									{
										if(map[x][y])
										{
											auto tempTransform = transform;
											tempTransform.Position.x = (float)x;
											tempTransform.Position.z = (float)y;
											tempTransform.Position.y = -4.0f;
											tempTransform.Scale = {0.5f, 0.5f, 0.5f};
											if(model.Model)
											{
												for (auto& mesh : model.Model->GetMeshes())
												{
													Renderer::SubmitMesh(mesh.GetMeshVertexArray(), mesh.GetMeshMaterial(), sceneLights, tempTransform.GetTransform());
												}
											}
										}
									}
								}

								/*for(int x = pos.x; x < end.x; x++)
								{
									for(int y = pos.y; y < end.y; y++)
									{
										auto tempTransform = transform;
										tempTransform.Position.x = array[x][y].position.x;
										tempTransform.Position.z = array[x][y].position.y;
										tempTransform.Position.y = -4;
										tempTransform.Scale = {0.1, 0.1, 0.1};
										if(model.Model)
										{
											for (auto& mesh : model.Model->GetMeshes())
											{
												Renderer::SubmitMesh(mesh.GetMeshVertexArray(), mesh.GetMeshMaterial(), sceneLights, tempTransform.GetTransform());
											}
										}
									}
								}*/
							}
						}	
					}
				}
#pragma endregion

#pragma region AudioListeners

				//Handles audio listeners
				{
					auto view = m_Registry.view<TransformComponent, AudioListenerComponent>();
					for(auto entity : view)
					{
						auto& listen = view.get<AudioListenerComponent>(entity);
						auto& transform = view.get<TransformComponent>(entity);

						if(listen.m_ActiveListing)
							Audio::SetListener(transform);
						
						// auto hear = m_Registry.view<AudioSource>();
						// for(auto sound : hear)
						// {
						//		if(sound.m_3D)
						// 		//Call a OnAudioListen type function where we can check distance
						// }
					}
				}

#pragma endregion
				
#pragma region AudioSource
				
				//Handle audio
				{
					auto view = m_Registry.view<TransformComponent, AudioSourceComponent>();
					for(auto entity : view)
					{
						auto& sound = view.get<AudioSourceComponent>(entity);
						auto& transform = view.get<TransformComponent>(entity);

						if(sound.m_Loaded)
						{
							Audio::UpdateSound(sound, transform);
						}
						else if(sound.GetStartLoad())
						{
							sound.m_Loaded = Audio::AddAudioSource(sound);
						}
					}
				}


				{
					auto objects = m_Registry.view<Affordance, TransformComponent>();
					auto view = m_Registry.view<AIComponent, CharacterComponent, TransformComponent, RigidBodyComponent>();
					auto player = m_Registry.view<PlayerInteractions, TransformComponent>();
					auto view2 = m_Registry.view<AStarComponent, MeshComponent, TransformComponent>();
					bool playerClose = false;
					mPlayerInteractions = false;
					mTargetString = "";
				
					for(auto entity : view)
					{
						auto &t = view.get<TransformComponent>(entity);
						auto &ai = view.get<AIComponent>(entity);
						auto &c = view.get<CharacterComponent>(entity);
						auto &rb = view.get<RigidBodyComponent>(entity);
						int i = 0;
						for(auto obj : objects)
						{
							auto & objTrasnform = objects.get<TransformComponent>(obj);
							auto & affordance = objects.get<Affordance>(obj);

							if(glm::distance(objTrasnform.Position, t.Position) < c.aiCharacter->GetDistance())
							{
									float affordanceValue = affordance.GetActionValue(c.aiCharacter->GetDesiredAction());
									auto event = c.aiCharacter->CheckAction(affordanceValue, glm::distance(objTrasnform.Position, t.Position), affordance.GetTag());
								
									if(event.second)
									{
										Int2 new_pos = AStar::GenerateRandomPosition(Int2((int)objTrasnform.Position.x, (int)objTrasnform.Position.z)).position;
										switch (c.aiCharacter->GetDesiredAction())
										{
										case Actions::drink:
										case Actions::pickup:
											objTrasnform.Position.x = (float)new_pos.x;
											objTrasnform.Position.z = (float)new_pos.y;
											break;
										default:
											break;
										}
									}
							}
						}
						
						if(!playerClose)
						{
							for(auto p : player)
							{
								auto & playerTransform = player.get<TransformComponent>(p);
								auto & interactions = player.get<PlayerInteractions>(p);

								if(glm::distance(playerTransform.Position, t.Position) < interactions.distance)
								{
									mPlayerInteractions = true;
									if(Input::IsKeyPressed(Key::U))
									{
										c.aiCharacter->ApplyPlayerAction(PlayerActions::pumpUp);
									}
									else if(Input::IsKeyPressed(Key::I))
									{
										c.aiCharacter->ApplyPlayerAction(PlayerActions::calm);
									}
									else if(Input::IsKeyPressed(Key::P))
									{
										c.aiCharacter->ApplyPlayerAction(PlayerActions::compliment);
									}
									else if(Input::IsKeyPressed(Key::O))
									{
										c.aiCharacter->ApplyPlayerAction(PlayerActions::insult);
									}
									mTargetString = c.aiCharacter->CharacterString();
									playerClose = true;
								}
							}	
						}

						ai.SetTargetPosition(c.aiCharacter->OnUpdate(deltaTime, t));
						ai.SetWander(c.aiCharacter->GetWander());
						ai.SetMovementSpeed(c.aiCharacter->GetSpeed());
						ai.OnUpdate(deltaTime, t);
						if(Application::Get().GetDebugModeStatus())
						{
							for(auto entity : view2)
							{
								auto& model = view2.get<MeshComponent>(entity);
								auto& transform = view2.get<TransformComponent>(entity);
							
								auto queue = ai.GetPositions();
								for(auto& nodes : queue)
								{
									auto tempTransform = transform;
									tempTransform.Position.x = (float)nodes.position.x;
									tempTransform.Position.z = (float)nodes.position.y;
									tempTransform.Position.y = -4.0f;
									tempTransform.Scale = {0.25f, 0.25f, 0.25f};
									tempTransform.Rotation = {0.0f, 0.0f, 0.0f};
									if(model.Model)
									{
										for (auto& mesh : model.Model->GetMeshes())
										{
											Renderer::SubmitMesh(mesh.GetMeshVertexArray(), mesh.GetMeshMaterial(), sceneLights, tempTransform.GetTransform());
										}
									}
								}	
						}
							
					}
						rb.Body->OnUpdate(t);
				}
					}

				Physics::PhysicsEngine::OnFixedUpdate(deltaTime, PhysicsTimestep(), m_Registry);
				AStar::Update();
				
#pragma endregion 

				Renderer::EndScene();
			}
#pragma endregion

#pragma region FramebufferEndings
			passes++;
		}while(passes < m_RenderPasses);

		//Only need to call this on one buffer as its always going to bind FBO 0 ie no framebuffer
		if(m_IsEditorScene) m_EditorSceneFramebuffer->Unbind();
#pragma endregion
		
	}
#pragma endregion SceneUpdate

#pragma  region ScenePhyscisUpdate
	
	void Scene::OnFixedUpdate(Timestep deltaTime, PhysicsTimestep physicsDeltaTime)
	{
#pragma region PhysicsStep
			
#pragma endregion 
	}
	
#pragma endregion ScenePhyscisUpdate

#pragma region SceneHelpers
	glm::mat4 Scene::GetTransformRelativeToParent(GameObject gameObject)
	{
		glm::mat4 transform(1.0f);

		GameObject parent = FindEntityByUUID(gameObject.GetParentUUID());
		if (parent)
			transform = GetTransformRelativeToParent(parent);

		return transform * gameObject.Transform().GetTransform();
	}

	GameObject& Scene::CreateGameObject(const std::string& name)
	{
		GameObject go = { m_Registry.create(), this };
		auto& idComponent = go.AddComponent<IDComponent>();
		idComponent.ID = {};
		go.AddComponent<TransformComponent>();
		if (!name.empty())
		{
			go.AddComponent<TagComponent>(name);
		}

		go.AddComponent<RelationshipComponent>();

		
		m_GameObjectsInScene[idComponent.ID] = go;
		return m_GameObjectsInScene[idComponent.ID];
	}

	


	GameObject Scene::CreateGameObject()
	{
		GameObject go = { m_Registry.create(), this };
		auto& idComponent = go.AddComponent<IDComponent>();
		idComponent.ID = {};
		go.AddComponent<TransformComponent>();
		go.AddComponent<TagComponent>("Default");

		go.AddComponent<RelationshipComponent>();

		m_GameObjectsInScene[idComponent.ID] = go;
		return go;
	}

	GameObject Scene::CreateEditorCamera()
	{
		auto go = CreateGameObject("Editor Camera");
		auto& c = go.AddComponent<EditorCameraComponent>();
		auto& t = go.GetComponent<TransformComponent>();
		c.EditorCamera.SetViewportSize(1280, 720);
		t.Position = {0,0,0};
		Texture3DProperties properties = {{"Resources/textures/default/skybox/default_linear_skybox.ktx2"}};
		go.AddComponent<SkyboxComponent>(properties);
		m_EditorCamera = go.GetUUID();
		return go;
	}

	void Scene::Destroy()
	{
		m_EditorGameFramebuffer->~Framebuffer();
		m_EditorSceneFramebuffer->~Framebuffer();
		Audio::Clear();
		//m_EditorCamera->~GameObject();
		//m_ActiveCamera ->~GameObject();
		//m_SceneLight->~GameObject();
		
	}

	GameObject Scene::FindEntityByTag(const std::string& tag)
	{
		auto view = m_Registry.view<TagComponent>();
		for (auto entity : view)
		{
			const auto& canditate = view.get<TagComponent>(entity).Tag;
			if (canditate == tag)
				return GameObject(entity, this);
		}

		return GameObject{};
	}

	GameObject Scene::FindEntityByUUID(UUID id)
	{
		auto view = m_Registry.view<IDComponent>();
		for (auto entity : view)
		{
			auto& idComponent = m_Registry.get<IDComponent>(entity);
			if (idComponent.ID == id)
				return GameObject(entity, this);
		}

		return GameObject{};
	}


	GameObject& Scene::FindGameObjectByID(const entt::entity& id)
	{
		try
		{
			for(auto& go : m_GameObjectsInScene)
			{
				if(go.second.GetID() == id)
				{
					return go.second;
				}
			}

			throw "GameObject not found!";
		}
		catch (const char* error)
		{
			TNAH_CORE_INFO("{0}", error);
		}
	}
	
	void Scene::DestroyGameObject(GameObject gameObject)
	{
		m_Registry.destroy(gameObject.GetID());
	}

	GameObject& Scene::GetSceneCamera()
	{
		return m_GameObjectsInScene[m_ActiveCamera];
	}

	GameObject& Scene::GetSceneLight()
	{
		return m_GameObjectsInScene[m_SceneLight];
	}
#pragma endregion 
	
}

