#pragma once

#include <TNAH/Core/Core.h>
#include "TNAH/Core/KeyCodes.h"
#include "TNAH/Core/UUID.h"
#include "ComponentIdentification.h"
#include "TNAH/Scene/SceneCamera.h"
#include "SkyboxComponent.h"
#include "TerrainComponent.h"
#include "PhysicsComponents.h"
#include "LightComponents.h"
#include "AudioComponents.h"
#include "AI/Affordance.h"
#include "AI/AIComponent.h"
#include "AI/CharacterComponent.h"
#include "AI/PlayerInteractions.h"

#include "TNAH/Renderer/Mesh.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


#include "TNAH/Core/Input.h"
#include "TNAH/Core/Math.h"

namespace tnah {

	

	/**********************************************************************************************//**
	 * @class	IDComponent
	 *
	 * @brief	An identifier component.
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 **************************************************************************************************/

	class IDComponent
	{
	public:
		UUID ID = 0;
		
	
	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "id component";
		inline static ComponentTypes s_Types = {
			{ComponentVariations::ID},
{{ComponentCategory::Core}}
		};
	};

	/**********************************************************************************************//**
	 * @class	TagComponent
	 *
	 * @brief	A tag component.
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 **************************************************************************************************/

	class TagComponent
	{
	public:
		std::string Tag;

		/**********************************************************************************************//**
		 * @fn	TagComponent::TagComponent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		TagComponent() = default;

		/**********************************************************************************************//**
		 * @fn	TagComponent::TagComponent(const TagComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		TagComponent(const TagComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	TagComponent::TagComponent(const std::string& tag)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	tag	The tag.
		 **************************************************************************************************/

		TagComponent(const std::string& tag)
			: Tag(tag) {}

		/**********************************************************************************************//**
		 * @fn	operator std::string& ()
		 *
		 * @brief	Cast that converts the given  to a string&amp;
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The result of the operation.
		 **************************************************************************************************/

		operator std::string& () { return Tag; }

		/**********************************************************************************************//**
		 * @fn	operator const std::string& () const
		 *
		 * @brief	Gets the string&amp;
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	A const.
		 **************************************************************************************************/

		operator const std::string& () const { return Tag; }
	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "tag component";
		inline static ComponentTypes s_Types= {
			{ComponentVariations::Tag},
{{ComponentCategory::Core}}
		};
	};

	/**********************************************************************************************//**
	 * @class	RelationshipComponent
	 *
	 * @brief	A relationship component.
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 **************************************************************************************************/

	class RelationshipComponent
	{
	public:

		/** @brief	Handle of the parent */
		UUID ParentHandle = 0;

		/** @brief	The children */
		std::vector<UUID> Children;

		/**********************************************************************************************//**
		 * @fn	RelationshipComponent::RelationshipComponent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		RelationshipComponent() = default;

		/**********************************************************************************************//**
		 * @fn	RelationshipComponent::RelationshipComponent(const RelationshipComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		RelationshipComponent(const RelationshipComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	RelationshipComponent::RelationshipComponent(UUID parent)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	parent	The parent.
		 **************************************************************************************************/

		RelationshipComponent(UUID parent)
			: ParentHandle(parent) {}
	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "relationship component";
		
	inline static ComponentTypes s_Types= {
                {ComponentVariations::Relationship},
    {{ComponentCategory::Core}}
		};
		
	};


	/**********************************************************************************************//**
	 * @class	TransformComponent
	 *
	 * @brief	Transform component, placed on every object to give it a real transform in the scene
	 * 			i.e. Position, Rotation and Scale. Including a raw 4x4 matrix transform (mat4)
	 * 			matrix for rendering
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	class TransformComponent
	{
	public:

		/** @brief	The position */
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };


		/** @brief	The rotation */
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };

		glm::quat QuatRotation = {1.0f, 0.0f, 0.0f, 0.0f};

		/** @brief	The scale */
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };


		/** @brief	The up */
		glm::vec3 Up = { 0.0f, 1.0f, 0.0f };


		/** @brief	The right */
		glm::vec3 Right = { 1.0f, 0.0f, 0.0f };


		/** @brief	The forward */
		glm::vec3 Forward = { 0.0f, 0.0f, -1.0f };

		/**********************************************************************************************//**
		 * @fn	TransformComponent::TransformComponent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		TransformComponent() = default;

		/**********************************************************************************************//**
		 * @fn	TransformComponent::TransformComponent(const TransformComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		TransformComponent(const TransformComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	TransformComponent::TransformComponent(const glm::vec3& position)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	position	The position.
		 **************************************************************************************************/

		TransformComponent(const glm::vec3& position)
			: Position(position) {}

		/**********************************************************************************************//**
		 * @fn	TransformComponent::TransformComponent(const glm::vec3& position, const glm::vec3& rotation,const glm::vec3& scale)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	position	The position.
		 * @param 	rotation	The rotation.
		 * @param 	scale   	The scale.
		 **************************************************************************************************/

		TransformComponent(const glm::vec3& position, const glm::vec3& rotation,const glm::vec3& scale)
			:Position(position), Rotation(rotation), Scale(scale) {}

		/**********************************************************************************************//**
		 * @fn	glm::mat4 TransformComponent::GetTransform() const
		 *
		 * @brief	Gets the transform
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The transform.
		 **************************************************************************************************/

		glm::mat4 GetTransform() const
		{
			return glm::translate(glm::mat4(1.0f), Position)
				* glm::toMat4(glm::quat(Rotation))
				* glm::scale(glm::mat4(1.0f), Scale);
		}

		glm::mat4 GetQuatTransform() const
		{
						return glm::translate(glm::mat4(1.0f), Position)
            				* glm::toMat4(QuatRotation)
            				* glm::scale(glm::mat4(1.0f), Scale);
		}

	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "transform component";
		inline static ComponentTypes s_Types= {
			{ComponentVariations::Transform},
{{ComponentCategory::Core}}
		};
	};

	/**********************************************************************************************//**
	 * @enum	CameraClearMode
	 *
	 * @brief	Values that represent camera clear modes
	 **************************************************************************************************/

	enum class CameraClearMode { Skybox, Color, None};
	/**********************************************************************************************//**
	 * @struct	CameraComponent
	 *
	 * @brief	A camera component that holds all the required information for a camera
	 *
	 * @author	Nukee
	 * @date	3/08/2021
	 **************************************************************************************************/

	class CameraComponent
	{
	public:

		/** @brief	The camera */
		SceneCamera Camera;

		/** @brief	The clear mode */
		CameraClearMode ClearMode = CameraClearMode::Skybox;

		/** @brief	The clear color */
		glm::vec4 ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };

		/** @brief	True to primary */
		bool Primary = true;

		

		/**********************************************************************************************//**
		 * @fn	void CameraComponent::SetClearMode(const CameraClearMode& mode)
		 *
		 * @brief	Sets clear mode
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	mode	The mode.
		 **************************************************************************************************/

		void SetClearMode(const CameraClearMode& mode)
		{
			if(mode != ClearMode)
			{
				ClearMode = mode;
				m_UpdatedClear = true;
			}
		}

		/**********************************************************************************************//**
		 * @fn	CameraComponent::CameraComponent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		CameraComponent() = default;

		/**********************************************************************************************//**
		 * @fn	CameraComponent::CameraComponent(const CameraComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		CameraComponent(const CameraComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	CameraComponent::CameraComponent(const SceneCamera& camera)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	camera	The camera.
		 **************************************************************************************************/

		CameraComponent(const SceneCamera& camera)
		{
			Camera = camera;
		}

		/**********************************************************************************************//**
		 * @fn	operator CameraComponent::SceneCamera& ()
		 *
		 * @brief	Cast that converts the given  to a SceneCamera&amp;
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The result of the operation.
		 **************************************************************************************************/

		operator SceneCamera& () { return Camera; }

		/**********************************************************************************************//**
		 * @fn	operator const CameraComponent::SceneCamera& () const
		 *
		 * @brief	Scene camera&amp;
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	A const.
		 **************************************************************************************************/

		operator const SceneCamera& () const { return Camera; }
	private:

		/** @brief	True to updated clear */
		bool m_UpdatedClear = false;
		inline static std::string s_SearchString = "camera component";
		inline static ComponentTypes s_Types = {
			{ComponentVariations::Camera},
{{ComponentCategory::Camera, ComponentCategory::Rendering}}
		};
		friend class EditorUI;
	};

	


	/**********************************************************************************************//**
	 * @struct	MeshComponent
	 *
	 * @brief	A mesh component holds all the information to do with 3D meshes
	 *
	 * @author	Bryce Standley
	 * @date	3/08/2021
	 **************************************************************************************************/

	class MeshComponent
	{
	public:

		/** @brief	The model */
		Ref<Model> Model = nullptr;

		

		/**********************************************************************************************//**
		 * @fn	MeshComponent::MeshComponent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		MeshComponent() = default;

		/**********************************************************************************************//**
		 * @fn	MeshComponent::MeshComponent(const std::string& modelPath)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	modelPath	Full pathname of the model file.
		 **************************************************************************************************/

		MeshComponent(const std::string& modelPath)
		{
			Model = Model::Create(modelPath);
		}

		/**********************************************************************************************//**
		 * @fn	MeshComponent::MeshComponent(const MeshComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		MeshComponent(const MeshComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	MeshComponent::MeshComponent(Ref<tnah::Model> model)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	model	The model.
		 **************************************************************************************************/

		MeshComponent(Ref<tnah::Model> model)
			: Model(model)
		{
		}

		/**********************************************************************************************//**
		 * @fn	void MeshComponent::LoadMesh(const std::string& modelPath)
		 *
		 * @brief	Loads a mesh
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	modelPath	Full pathname of the model file.
		 **************************************************************************************************/

		void LoadMesh(const std::string& modelPath)
		{
			Model = Model::Create(modelPath);
		};

		/**********************************************************************************************//**
		 * @fn	operator Ref<tnah::Model>() const
		 *
		 * @brief	Cast that converts the given  to a Model>
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The result of the operation.
		 **************************************************************************************************/

		operator Ref<tnah::Model>() const { return Model; }
	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "mesh component";
		inline static ComponentTypes s_Types = {
			{ComponentVariations::Mesh},
{{ComponentCategory::Rendering, ComponentCategory::Objects}}
		};
	};

	/**********************************************************************************************//**
	 * @enum	MovementType
	 *
	 * @brief	Values that represent movement types
	 **************************************************************************************************/

	enum class MovementType
	{
		Direct, Physics
	};

	/**********************************************************************************************//**
	 * @class	PlayerControllerComponent
	 *
	 * @brief	A player controller component.
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 **************************************************************************************************/

	class PlayerControllerComponent
	{
	public:
		
		/** @brief	The forward */
		KeyCode Forward = Key::W;

		/** @brief	The backward */
		KeyCode Backward = Key::S;
		
		/** @brief	The left */
		KeyCode Left = Key::A;
		
		/** @brief	The right */
		KeyCode Right = Key::D;

		/** @brief	The sprint */
		std::pair<KeyCode, KeyCode> Sprint = {Key::LeftShift, Key::RightShift};
		/** @brief	The jump */
		KeyCode Jump = Key::Space;
		/** @brief	The crouch */
		KeyCode Crouch = Key::C;
		/** @brief	The movement style */
		MovementType MovementStyle = MovementType::Direct;

		/** @brief	Height of the player */
		float PlayerHeight = 3.5f;
		/** @brief	The movement speed */
		float MovementSpeed = 5.0f;
		/** @brief	The rotation sensitivity */
		float RotationSensitivity = 0.1f;
		/** @brief	The sprint speed */
		float SprintSpeed = 10.0f;
		/** @brief	The crouch speed */
		float CrouchSpeed = 2.5f;
		/** @brief	The crouch height multiplier */
		float CrouchHeightMultiplier = 0.5f;

		

		/**********************************************************************************************//**
		 * @fn	PlayerControllerComponent::PlayerControllerComponent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		PlayerControllerComponent() = default;

		/**********************************************************************************************//**
		 * @fn	bool PlayerControllerComponent::IsSprinting() const
		 *
		 * @brief	Query if this object is sprinting
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	True if sprinting, false if not.
		 **************************************************************************************************/

		bool IsSprinting() const { return Input::IsKeyPressed(Sprint.first) || Input::IsKeyPressed(Sprint.second); }

		/**********************************************************************************************//**
		 * @fn	bool PlayerControllerComponent::IsCrouched() const
		 *
		 * @brief	Query if this object is crouched
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	True if crouched, false if not.
		 **************************************************************************************************/

		bool IsCrouched() const { return Input::IsKeyPressed(Crouch); }

		/**********************************************************************************************//**
		 * @fn	bool PlayerControllerComponent::IsJumping() const
		 *
		 * @brief	Query if this object is jumping
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	True if jumping, false if not.
		 **************************************************************************************************/

		bool IsJumping() const { return Input::IsKeyPressed(Jump); }

		/**********************************************************************************************//**
		 * @fn	bool PlayerControllerComponent::IsMoving() const
		 *
		 * @brief	Query if this object is moving
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	True if moving, false if not.
		 **************************************************************************************************/

		bool IsMoving() const { return Input::IsKeyPressed(Forward) || Input::IsKeyPressed(Backward) ||
			Input::IsKeyPressed(Left) || Input::IsKeyPressed(Right); }

		/**********************************************************************************************//**
		 * @fn	void PlayerControllerComponent::SetActive(const bool& active)
		 *
		 * @brief	Sets an active
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	active	True to active.
		 **************************************************************************************************/

		void SetActive(const bool& active) { m_Active = active; }

		/**********************************************************************************************//**
		 * @fn	bool PlayerControllerComponent::IsActive() const
		 *
		 * @brief	Query if this object is active
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	True if active, false if not.
		 **************************************************************************************************/

		bool IsActive() const{ return m_Active; }
	
	private:

		/**********************************************************************************************//**
		 * @fn	void PlayerControllerComponent::ProcessMouseRotation(TransformComponent& transform)
		 *
		 * @brief	Process the mouse rotation described by transform
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param [in,out]	transform	The transform.
		 **************************************************************************************************/

		void ProcessMouseRotation(TransformComponent& transform)
		{
			const auto [fst, snd] = Input::GetMousePos();
			if (m_FirstMouseInput)
			{
				m_LastMouseXPos = fst;
				m_LastMouseYPos = snd;
				m_FirstMouseInput = false;
			}
			float offsetX = fst - m_LastMouseXPos;
			float offsetY = m_LastMouseYPos - snd;
			m_LastMouseXPos = fst;
			m_LastMouseYPos = snd;
			offsetX *= RotationSensitivity;
			offsetY *= RotationSensitivity;
			transform.Rotation.x += offsetX;
			transform.Rotation.y -= offsetY;
			if (transform.Rotation.y > 89.0f)
			{
				transform.Rotation.y = 89.0f;
			}
			if (transform.Rotation.y < -89.0f)
			{
				transform.Rotation.y = -89.0f;
			}
		}

		/** @brief	True to active */
		bool m_Active = true;
		/** @brief	True to first mouse input */
		bool m_FirstMouseInput = true;
		/** @brief	The last mouse x coordinate position */
		float m_LastMouseXPos = 0.0f;
		/** @brief	The last mouse y coordinate position */
		float m_LastMouseYPos = 0.0f;
		/** @brief	True to disable, false to enable the mouse */
		bool m_MouseDisabled = false;

		inline static std::string s_SearchString = "player controller component";
		inline static ComponentTypes s_Types = {
			{ComponentVariations::PlayerController},
{{ComponentCategory::Controls, ComponentCategory::Objects}}
		};
		friend class Scene;
		friend class EditorUI;
		
	};

	/**********************************************************************************************//**
	 * @class	EditorCameraComponent
	 *
	 * @brief	An editor camera component.
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 **************************************************************************************************/

	class EditorCameraComponent
	{
	public:
		/** @brief	The editor camera */
		SceneCamera EditorCamera;
		/** @brief	The clear mode */
		CameraClearMode ClearMode = CameraClearMode::Skybox;
		/** @brief	The clear color */
		glm::vec4 ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };
		/** @brief	True to primary */
		bool Primary = true;

		

		/**********************************************************************************************//**
		 * @fn	void EditorCameraComponent::SetClearMode(const CameraClearMode& mode)
		 *
		 * @brief	Sets clear mode
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	mode	The mode.
		 **************************************************************************************************/

		void SetClearMode(const CameraClearMode& mode)
		{
			if(mode != ClearMode)
			{
				ClearMode = mode;
			}
		}

		/**********************************************************************************************//**
		 * @fn	EditorCameraComponent::EditorCameraComponent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		EditorCameraComponent() = default;

		/**********************************************************************************************//**
		 * @fn	EditorCameraComponent::EditorCameraComponent(const EditorCameraComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		EditorCameraComponent(const EditorCameraComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	operator EditorCameraComponent::SceneCamera& ()
		 *
		 * @brief	Cast that converts the given  to a SceneCamera&amp;
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The result of the operation.
		 **************************************************************************************************/

		operator SceneCamera& () { return EditorCamera; }

		/**********************************************************************************************//**
		 * @fn	operator const EditorCameraComponent::SceneCamera& () const
		 *
		 * @brief	Scene camera&amp;
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	A const.
		 **************************************************************************************************/

		operator const SceneCamera& () const { return EditorCamera; }
	private:
		inline static std::string s_SearchString = "editor camera component";
		inline static ComponentTypes s_Types = {
			{ComponentVariations::EditorCamera},
{{ComponentCategory::Core, ComponentCategory::Camera, ComponentCategory::Editor}}
		};
		friend class Scene;
		friend class EditorUI;
	};
	
	/**
	 *	@class EditorComponent
	 *
	 *	@brief A component that's placed on a editor camera to control and maintain editor related controls and values.
	 *
	 *	@author Bryce Standley
	 *	@date 21/08/2021
	 */
	class EditorComponent
	{
	public:

		
		/**********************************************************************************************//**
		 * @fn	EditorComponent::EditorComponent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		EditorComponent() = default;
		
	private:

		/**********************************************************************************************//**
		 * @enum	EditorMode
		 *
		 * @brief	Values that represent editor modes
		 **************************************************************************************************/

		enum class EditorMode
		{
			Edit, Play, Pause
		};

		/** @brief	The editor mode */
		EditorMode m_EditorMode = EditorMode::Edit;

		/** @brief	True if is empty, false if not */
		bool m_IsEmpty = true;
		
		/** @brief	The search string */
		inline static std::string s_SearchString = "editor component";
		inline static ComponentTypes s_Types = {
			{ComponentVariations::Editor},
{{ComponentCategory::Core, ComponentCategory::Editor}}
		};
		friend class Scene;
		friend class EditorLayer;
		friend class EditorUI;
		friend class Editor;
	};

	/**********************************************************************************************//**
	 * @struct	NativeScript
	 *
	 * @brief	A native script component allows the user to create overrides that will attach to the
	 * 			game object. Native scripts are written in C++ and provided within the application using
	 * 			the engine.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	class NativeScriptComponent
	{
	public:

		std::string Script;

		
		
		NativeScriptComponent() = default;
		NativeScriptComponent(const std::string& scriptPath)
			:Script(scriptPath) {}
	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "";
		inline static ComponentTypes s_Types = {
			{ComponentVariations::NativeScript},
{{ComponentCategory::Script, ComponentCategory::Custom}}
		};
	};

	/**********************************************************************************************//**
	 * @struct	CSharpScript
	 *
	 * @brief	A C# script component allows the user to create overrides attached to the game object
	 * 			within the application using the engine. A C# script is written in C# and provided 
	 * 			within the application using the engine.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct CSharpScript 
	{
	};

}
