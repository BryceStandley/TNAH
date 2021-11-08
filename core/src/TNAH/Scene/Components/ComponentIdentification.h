#pragma once

namespace tnah {

	/**********************************************************************************************//**
	* @enum	ComponentVariations
	*
	* @brief	Values that represent component types
	**************************************************************************************************/

	enum class ComponentVariations
	{
		None,
		ID, Tag, Relationship, Transform, NativeScript, CSharpScript,
		Camera, EditorCamera, Editor, Skybox, Light,
		Terrain, Mesh, PlayerController, AudioSource, AudioListener,
		Rigidbody, AiCharacter, AStar, AStarObstacle, Affordance
	};

	/**********************************************************************************************//**
	* @enum	ComponentCategory
	*
	* @brief	Values that represent the base type of a component and what category they belong to.
	**************************************************************************************************/
	enum class ComponentCategory
	{
		Core, Editor, Camera, Lighting, Controls, Audio,
		Physics, Rendering, Environment, Objects, Script, AI, Emotion, Custom
	};

	/**********************************************************************************************//**
	* @struct	ComponentTypes
	*
	* @brief	Structure of a component identification. Used to find and list components within the editor
	**************************************************************************************************/
	struct ComponentTypes
	{
		ComponentVariations Component;
		std::list<ComponentCategory> Categories;
	};

	
}