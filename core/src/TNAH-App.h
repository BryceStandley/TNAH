#pragma once

//This header is a combined header of all components of the engine
// Use this header in any applications that require access to structures and classes 
// within the engine

// NOTE any application needs to #include <TNAH.h> in their main Application cpp file 
// to enable the entry point of the application, not doing this will result in build errors

//To include in all applications that use the TNAH-Engine!
#include "TNAH/Core/Core.h"

// --- TNAH Engine Components --- //
#include "TNAH/Core/Application.h"
#include "TNAH/Core/Log.h"
#include "TNAH/Core/FileStructures.h"
#include "TNAH/Core/Input.h"
#include "TNAH/Core/KeyCodes.h"
#include "TNAH/Core/MouseCodes.h"
#include "TNAH/Core/Math.h"
#include "TNAH/Core/FileManager.h"
#include "TNAH/Core/Singleton.h"

#include "TNAH/Core/Timestep.h"
#include "TNAH/Physics/PhysicsTimestep.h"

#include "TNAH/Layers/Layer.h"
#include "TNAH/Layers/ImGuiLayer.h"

#include "TNAH/Scene/Components/Components.h"
#include "TNAH/Scene/Scene.h"
#include "TNAH/Scene/GameObject.h"
#include "TNAH/Scene/Light/DirectionalLight.h"
#include "TNAH/Scene/Light/PointLight.h"
#include "TNAH/Scene/Light/SpotLight.h"

#include "TNAH/Scene/SceneCamera.h"
#include "TNAH/Renderer/Renderer.h"
#include "TNAH/Renderer/RenderCommand.h"
#include "TNAH/Renderer/RenderingBuffers.h"
#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/VertexArray.h"

// Editor
#include "TNAH/Editor/EditorUI.h"

//Audio
#include "TNAH/Audio/Audio.h"


