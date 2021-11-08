#pragma once
#include <TNAH/Core/Core.h>
#include "Components/Components.h"
#include "Scene.h"
#pragma warning(push, 0)
#include "entt.hpp"
#pragma warning(pop)

namespace tnah {

	/**
	 * @class	GameObject
	 *
	 * @brief	The GameObject class is used for creating gameobjects
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	class GameObject
	{
	public:

		/**
		 * @fn	GameObject::GameObject() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		GameObject() = default;
		

		/**
		 * @fn	GameObject::GameObject(entt::entity id, Scene* scene)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 		  	id   	The identifier.
		 * @param [in,out]	scene	If non-null, the scene.
		 */

		GameObject(entt::entity id, Scene* scene)
			: m_EntityID(id), m_Scene(scene)
		{
		}

		/**
		 * @fn	GameObject::~GameObject()
		 *
		 * @brief	Destructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		~GameObject()
		{
		}

		

		/**
		 * @fn	template<typename T, typename... Args> inline T& GameObject::AddComponent(Args&&... args)
		 *
		 * @brief	Adds a component to a game object
		 *
		 * @tparam	T   	Generic type parameter.
		 * @tparam	Args	Type of the arguments.
		 * @param 	args	Variable arguments providing [in,out] The arguments.
		 *
		 * @returns	A reference to a component.
		 */

		template<typename T, typename... Args>
		inline T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>()) 
			{
				TNAH_CORE_ASSERT(HasComponent<T>(), "GameObject already has that component!");
				return GetComponent<T>(); 
			}
			FindComponentTypeFromTemplate<T>();
			return m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
			
		}

		/**
		 * @fn	template<typename T> inline T& GameObject::GetComponent()
		 *
		 * @brief	Gets the component of a game object
		 *
		 * @tparam	T	Generic type parameter.
		 *
		 * @returns	The component.
		 */

		template<typename T>
		inline T& GetComponent()
		{
			if (!HasComponent<T>()) 
			{ 
				TNAH_CORE_ASSERT(!HasComponent<T>(), "GameObject doesn't have that component! You need to add one with AddComponent<>(), Default component added!");
				return AddComponent<T>();
			}
			else
			{
				return m_Scene->m_Registry.get<T>(m_EntityID);
			}
		}

		/**
		 * @fn	template<typename T> inline bool GameObject::HasComponent()
		 *
		 * @brief	Query if this object has component
		 *
		 * @tparam	T	Generic type parameter.
		 *
		 * @returns	True if component, false if not.
		 */

		template<typename T>
		inline bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityID);
		}


		/**
		 * @fn	template<typename T> inline void GameObject::RemoveComponent()
		 *
		 * @brief	Removes the component from a game object
		 *
		 * @tparam	T	Generic type parameter.
		 */

		template<typename T>
		inline void RemoveComponent()
		{

			if (HasComponent<T>())
			{
				m_Scene->m_Registry.remove<T>(m_EntityID);
				return;
			}
			TNAH_CORE_ASSERT(false, "GameObject doesn't have that component! You can't remove what isn't there!");
		}

		/**
		 * @fn	inline void GameObject::Destroy()
		 *
		 * @brief	Destroys this object
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		inline void Destroy()
		{
			m_Scene->m_Registry.destroy(m_EntityID);
			delete this;
		}

		/**
		 * @fn	entt::entity GameObject::GetID()
		 *
		 * @brief	Gets the entity identifier
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The identifier.
		 */

		entt::entity GetID() { return m_EntityID; }

		/**
		 * @fn	TransformComponent& GameObject::Transform()
		 *
		 * @brief	Gets the transform
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	A reference to a TransformComponent.
		 */

		TransformComponent& Transform()
		{
			return m_Scene->m_Registry.get<TransformComponent>(m_EntityID);
		}

		/**
		 * @fn	const glm::mat4& GameObject::Transform() const
		 *
		 * @brief	Gets the transform
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	A reference to a const glm::mat4.
		 */

		const glm::mat4& Transform() const
		{
			return m_Scene->m_Registry.get<TransformComponent>(m_EntityID).GetTransform();
		}

		/**
		 * @fn	operator GameObject::uint32_t () const
		 *
		 * @brief	Cast that converts the given  to an uint32_t
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The result of the operation.
		 */

		operator uint32_t () const { return (uint32_t)m_EntityID; }

		/**
		 * @fn	operator entt::entity() const
		 *
		 * @brief	Cast that converts the given  to an entity
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The result of the operation.
		 */

		operator entt::entity() const { return m_EntityID; }

		/**
		 * @fn	operator GameObject::bool() const
		 *
		 * @brief	Cast that converts the given  to a bool
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The result of the operation.
		 */

		operator bool() const
		{
			return (m_EntityID != entt::null) && m_Scene;
		}

		/**
		 * @fn	bool GameObject::operator==(const GameObject& other) const
		 *
		 * @brief	Equality operator
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	other	The other.
		 *
		 * @returns	True if the parameters are considered equivalent.
		 */

		bool operator==(const GameObject& other) const
		{

			return m_EntityID == other.m_EntityID && m_Scene == other.m_Scene;
		}

		/**
		 * @fn	bool GameObject::operator!=(const GameObject& other) const
		 *
		 * @brief	Inequality operator
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	other	The other.
		 *
		 * @returns	True if the parameters are not considered equivalent.
		 */

		bool operator!=(const GameObject& other) const
		{
			return !(*this == other);
		}

		/**
		 * @fn	void GameObject::SetParentUUID(UUID parent)
		 *
		 * @brief	Sets parent uuid
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	parent	The parent.
		 */

		void SetParentUUID(UUID parent) { GetComponent<RelationshipComponent>().ParentHandle = parent; }

		/**
		 * @fn	UUID GameObject::GetParentUUID()
		 *
		 * @brief	Gets the parent uuid
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The parent uuid.
		 */

		UUID GetParentUUID() { return GetComponent<RelationshipComponent>().ParentHandle; }

		/**
		 * @fn	std::vector<UUID>& GameObject::Children()
		 *
		 * @brief	Gets the children
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	A reference to a std::vector&lt;UUID&gt;
		 */

		std::vector<UUID>& Children() { return GetComponent<RelationshipComponent>().Children; }

		/**
		 * @fn	bool GameObject::HasParent()
		 *
		 * @brief	Query if this object has parent
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	True if parent, false if not.
		 */

		bool HasParent()
		{
			return m_Scene->FindEntityByUUID(GetParentUUID());
		}

		/**
		 * @fn	bool GameObject::IsAncesterOf(GameObject& entity)
		 *
		 * @brief	Is ancester of the given entity
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param [in,out]	entity	The entity.
		 *
		 * @returns	True if ancester of, false if not.
		 */

		bool IsAncesterOf(GameObject& entity)
		{
			const auto& children = Children();

			if (children.size() == 0)
				return false;

			for (UUID child : children)
			{
				if (child == entity.GetUUID())
					return true;
			}

			for (UUID child : children)
			{
				if (m_Scene->FindEntityByUUID(child).IsAncesterOf(entity))
					return true;
			}

			return false;
		}

		/**
		 * @fn	bool GameObject::IsDescendantOf(GameObject entity)
		 *
		 * @brief	Is descendant of the given entity
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	entity	The entity.
		 *
		 * @returns	True if descendant of, false if not.
		 */

		bool IsDescendantOf(GameObject entity)
		{
			return entity.IsAncesterOf(*this);
		}

		/**
		 * @fn	UUID GameObject::GetUUID()
		 *
		 * @brief	Gets the uuid
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The uuid.
		 */

		UUID GetUUID() { return GetComponent<IDComponent>().ID; }

		/**
		 * @fn	void GameObject::SetTag(const std::string& tag);
		 *
		 * @brief	Sets a tag
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	tag	The tag.
		 */

		void SetTag(const std::string& tag);

		/**
		 * @fn	std::string GameObject::GetTag();
		 *
		 * @brief	Gets the tag
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The tag.
		 */

		std::string GetTag();

		/**
		 * @fn	void GameObject::SetActive(const bool& active)
		 *
		 * @brief	Sets whether or not the object is active
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	active	True to active, false to deactivate.
		 */

		void SetActive(const bool& active) { m_Active = active; }

		/**
		 * @fn	bool GameObject::IsActive() const
		 *
		 * @brief	Query if this object is active
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	True if active, false if not.
		 */

		bool IsActive() const { return m_Active; }

		/**
		 * @fn	std::vector<ComponentTypes> GameObject::GetComponentList() const
		 *
		 * @brief	Gets component list
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The component list.
		 */

		std::vector<ComponentVariations> GetComponentList() const { return m_HeldTypes; }

	private:

		/**
		 * @fn	template<typename T> void GameObject::FindComponentTypeFromTemplate()
		 *
		 * @brief	Searches for the first component type from template
		 *
		 * @tparam	T	Generic type parameter.
		 */

		template<typename T>

		void FindComponentTypeFromTemplate()
		{
			if(std::is_same_v<T, IDComponent>) { m_HeldTypes.emplace_back(ComponentVariations::ID); }
			if(std::is_same_v<T, TagComponent>) { m_HeldTypes.emplace_back(ComponentVariations::Tag); }
			if(std::is_same_v<T, RelationshipComponent>) { m_HeldTypes.emplace_back(ComponentVariations::Relationship); }
			if(std::is_same_v<T, TransformComponent>) { m_HeldTypes.emplace_back(ComponentVariations::Transform);  }
			if(std::is_same_v<T, CameraComponent>) { m_HeldTypes.emplace_back(ComponentVariations::Camera);  }
			if(std::is_same_v<T, EditorCameraComponent>) { m_HeldTypes.emplace_back(ComponentVariations::EditorCamera); }
			if(std::is_same_v<T, EditorComponent>) { m_HeldTypes.emplace_back(ComponentVariations::Editor);  }
			if(std::is_same_v<T, SkyboxComponent>) { m_HeldTypes.emplace_back(ComponentVariations::Skybox);  }
			if(std::is_same_v<T, LightComponent>) { m_HeldTypes.emplace_back(ComponentVariations::Light);  }
			if(std::is_same_v<T, TerrainComponent>) { m_HeldTypes.emplace_back(ComponentVariations::Terrain);  }
			if(std::is_same_v<T, MeshComponent>) { m_HeldTypes.emplace_back(ComponentVariations::Mesh);  }
			if(std::is_same_v<T, PlayerControllerComponent>) { m_HeldTypes.emplace_back(ComponentVariations::PlayerController); }
			if(std::is_same_v<T, AudioListenerComponent>) { m_HeldTypes.emplace_back(ComponentVariations::AudioListener);  }
			if(std::is_same_v<T, AudioSourceComponent>) { m_HeldTypes.emplace_back(ComponentVariations::AudioSource);  }
			if(std::is_same_v<T, RigidBodyComponent>) { m_HeldTypes.emplace_back(ComponentVariations::Rigidbody);  }
		}

		
		
	private:

		/** @brief	Identifier for the entity */
		entt::entity m_EntityID{ entt::null };

		/** @brief	The scene */
		Scene* m_Scene = nullptr;


		/** @brief	True to active */
		bool m_Active = true;

		/** @brief	vector of the held types*/
		std::vector<ComponentVariations> m_HeldTypes = {};

		/**
		 * @class	Scene
		 *
		 * @brief	A scene.
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		friend class Scene;

		/**
		 * @class	SceneSerializer
		 *
		 * @brief	An object for persisting scene data.
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		friend class SceneSerializer;

		/**
		 * @class	ScriptEngine
		 *
		 * @brief	A script engine.
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		friend class ScriptEngine;

		friend class PhysicsEvents;
	};
}

