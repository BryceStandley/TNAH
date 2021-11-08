#pragma once

#include <TNAH/Core/Core.h>
#include "TNAH/Core/UUID.h"
#include <vector>
#include "SceneCamera.h"
#include "Components/Components.h"
#include "TNAH/Core/Timestep.h"
#include "TNAH/Core/Math.h"
#include "TNAH/Core/Ref.h"
#include "TNAH/Physics/PhysicsTimestep.h"

#pragma warning(push, 0)
#include "entt.hpp"
#include <reactphysics3d/reactphysics3d.h>
#pragma warning(pop)

namespace tnah {

	/**
	 * @class	Light
	 *
	 * @brief	A light object forward declaration.
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	class Light;

	/**
	 * @class	GameObject
	 *
	 * @brief	A game object forward declaration.
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	class GameObject;

	/**********************************************************************************************//**
	 * @class	Scene
	 *
	 * @brief	A scene
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 **************************************************************************************************/

	class Scene : public RefCounted
	{
		friend class GameObject;
	public:

		/**********************************************************************************************//**
		 * @struct	ActiveScene
		 *
		 * @brief	The current active scene reference
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		struct ActiveScene
		{
			Ref<Scene> Scene;
			
		};

		/**********************************************************************************************//**
		 * @fn	Scene::Scene(bool editor = false);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	editor	(Optional) True to create a scene for the editor.
		 **************************************************************************************************/

		Scene(bool editor = false);

		/**********************************************************************************************//**
		 * @fn	Scene::~Scene();
		 *
		 * @brief	Destructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		~Scene();



		/**********************************************************************************************//**
		 * @fn	static void Scene::ClearActiveScene();
		 *
		 * @brief	Clears the active scene
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		static void ClearActiveScene();

		/**********************************************************************************************//**
		 * @fn	static Ref<Scene> Scene::CreateEmptyScene();
		 *
		 * @brief	Creates empty scene
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The new empty scene.
		 **************************************************************************************************/

		static Ref<Scene> CreateEmptyScene();

		/**********************************************************************************************//**
		 * @fn	void Scene::OnUpdate(Timestep deltaTime);
		 *
		 * @brief	Creates game object and adds a default transform component to it
		 *
		 * @author	Bryce Standley
		 * @date	18/07/2021
		 *
		 * @param 	deltaTime	The delta time.
		 *
		 * ### returns	The new game object.
		 **************************************************************************************************/

		void OnUpdate(Timestep deltaTime);

		/**********************************************************************************************//**
		 * @fn	void Scene::OnFixedUpdate(PhysicsTimestep deltaTime);
		 *
		 * @brief	Executes the 'fixed update' action
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	deltaTime	The delta time.
		 **************************************************************************************************/

		void OnFixedUpdate(Timestep deltaTime, PhysicsTimestep physicsDeltaTime);
		
		/**********************************************************************************************//**
		 * @fn	glm::mat4 Scene::GetTransformRelativeToParent(GameObject gameObject);
		 *
		 * @brief	Gets the parent of this item
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	gameObject	The game object.
		 *
		 * @returns	The transform relative to parent.
		 **************************************************************************************************/

		glm::mat4 GetTransformRelativeToParent(GameObject gameObject);

		/**********************************************************************************************//**
		 * @fn	GameObject& Scene::CreateGameObject(const std::string& name);
		 *
		 * @brief	Creates game object
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	name	The name.
		 *
		 * @returns	The new game object.
		 **************************************************************************************************/

		GameObject& CreateGameObject(const std::string& name);

		/**********************************************************************************************//**
		 * @fn	GameObject Scene::CreateGameObject();
		 *
		 * @brief	Creates game object
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The new game object.
		 **************************************************************************************************/

		GameObject CreateGameObject();

		/**********************************************************************************************//**
		 * @fn	GameObject Scene::FindEntityByTag(const std::string& tag);
		 *
		 * @brief	Searches for the first entity by tag
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	tag	The tag.
		 *
		 * @returns	The found entity by tag.
		 **************************************************************************************************/

		GameObject FindEntityByTag(const std::string& tag);

		/**********************************************************************************************//**
		 * @fn	GameObject Scene::FindEntityByUUID(UUID id);
		 *
		 * @brief	Searches for the first entity by uuid
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	id	The identifier.
		 *
		 * @returns	The found entity by uuid.
		 **************************************************************************************************/

		GameObject FindEntityByUUID(UUID id);

		/**********************************************************************************************//**
		 * @fn	GameObject& Scene::FindGameObjectByID(const entt::entity& id);
		 *
		 * @brief	Searches for the first game object by identifier
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	id	The identifier.
		 *
		 * @returns	The found game object by identifier.
		 **************************************************************************************************/

		GameObject& FindGameObjectByID(const entt::entity& id);

		/**********************************************************************************************//**
		 * @fn	void Scene::DestroyGameObject(GameObject gameObject);
		 *
		 * @brief	Destroys the game object described by gameObject
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	gameObject	The game object.
		 **************************************************************************************************/

		void DestroyGameObject(GameObject gameObject);

		/**********************************************************************************************//**
		 * @fn	GameObject& Scene::GetSceneCamera();
		 *
		 * @brief	Gets scene camera
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The scene camera.
		 **************************************************************************************************/

		GameObject& GetSceneCamera();

		/**********************************************************************************************//**
		 * @fn	GameObject& Scene::GetSceneLight();
		 *
		 * @brief	Gets scene light
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The scene light.
		 **************************************************************************************************/

		GameObject& GetSceneLight();

		/**********************************************************************************************//**
		* @fn	std::map<UUID, GameObject>& Scene::GetGameObjectsInScene();
		*
		* @brief	Gets game objects in scene
		*
		* @author	Chris
		* @date	10/09/2021
		*
		* @returns	The game objects in scene in a map.
		**************************************************************************************************/

		std::map<UUID, GameObject>& GetGameObjectsInScene();
		PhysicsTimestep m_PhysicsTime;
		bool GetPlayerInteraction() { return mPlayerInteractions; }
		std::string GetTargetString() const { return mTargetString; }private:

		/**********************************************************************************************//**
		 * @fn	GameObject Scene::CreateEditorCamera();
		 *
		 * @brief	Creates editor camera
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The new editor camera.
		 **************************************************************************************************/

		GameObject CreateEditorCamera();

		/**********************************************************************************************//**
		 * @fn	void Scene::Destroy();
		 *
		 * @brief	Destroys this object
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		void Destroy();

		/**********************************************************************************************//**
		 * @fn	static Ref<Scene> Scene::CreateNewEditorScene();
		 *
		 * @brief	Creates a new editor scene
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The new new editor scene.
		 **************************************************************************************************/

		static Ref<Scene> CreateNewEditorScene();

		/**********************************************************************************************//**
		 * @fn	GameObject& Scene::GetEditorCamera();
		 *
		 * @brief	Gets editor camera
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The editor camera.
		 **************************************************************************************************/

		GameObject& GetEditorCamera();

		/**********************************************************************************************//**
		 * @fn	Ref<Framebuffer> Scene::GetEditorSceneFramebuffer()
		 *
		 * @brief	Gets editor scene framebuffer
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The editor scene framebuffer.
		 **************************************************************************************************/

		Ref<Framebuffer> GetEditorSceneFramebuffer() { return m_EditorSceneFramebuffer; }

		/**********************************************************************************************//**
		 * @fn	Ref<Framebuffer> Scene::GetEditorGameFramebuffer()
		 *
		 * @brief	Gets editor game framebuffer
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The editor game framebuffer.
		 **************************************************************************************************/

		Ref<Framebuffer> GetEditorGameFramebuffer() { return m_EditorGameFramebuffer; }

		/**********************************************************************************************//**
		 * @fn	entt::registry& Scene::GetRegistry()
		 *
		 * @brief	Gets the registry
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The registry.
		 **************************************************************************************************/

		entt::registry& GetRegistry() { return m_Registry; }



		/**********************************************************************************************//**
		 * @fn	GameObject* Scene::GetRefGameObject(const UUID& id);
		 *
		 * @brief	Gets reference game object
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	id	The identifier.
		 *
		 * @returns	Null if it fails, else the reference game object.
		 **************************************************************************************************/

		GameObject* GetRefGameObject(const UUID& id);

	private:

		/** @brief	A active scene reference */
		static ActiveScene s_ActiveScene;
		
		/** @brief	The component registry */
		entt::registry m_Registry;
		
		/** @brief	The game objects in scene */
		std::map<UUID, GameObject> m_GameObjectsInScene;
		
		/** @brief	The active camera */
		UUID m_ActiveCamera;
		/** @brief	The scene light */
		UUID m_SceneLight;

		/** @brief	The editor camera */
		UUID m_EditorCamera;
		/** @brief	The editor scene framebuffer */
		Ref<Framebuffer> m_EditorSceneFramebuffer;
		/** @brief	The editor game framebuffer */
		Ref<Framebuffer> m_EditorGameFramebuffer;
		/** @brief	True if is editor scene, false if not */
		bool m_IsEditorScene = false;
		
		/** @brief	The render passes for scene rendering */
		uint32_t m_RenderPasses = 0;
		
		/** @brief	The scene entity */
		entt::entity m_SceneEntity;
		/** @brief	Identifier for the scene */
		UUID m_SceneID;

		/** @brief	The listener */
		rp3d::EventListener * listener;

		bool mPlayerInteractions;
		std::string mTargetString = "";
		
		friend class EditorLayer;
		friend class Editor;
		friend class Serializer;
	};


	

	

}