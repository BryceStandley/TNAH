target_precompile_headers(${PROJECT_NAME} PRIVATE
         tnahpch.h
        )

# Add source files.
target_sources(${PROJECT_NAME}
        PRIVATE
        TNAH/Audio/Audio.cpp
        TNAH/Audio/AudioAPI.cpp

        TNAH/Core/AABB.h
        TNAH/Core/Application.cpp
        TNAH/Core/Buffer.h
        TNAH/Core/Core.h
        TNAH/Core/EntryPoint.h
        TNAH/Core/FileManager.cpp
        TNAH/Core/FileStructures.h
        TNAH/Core/Input.h
        TNAH/Core/KeyCodes.h
        TNAH/Core/Log.cpp
        TNAH/Core/Math.cpp
        TNAH/Core/MouseCodes.h
        TNAH/Core/Ref.cpp
        TNAH/Core/Singleton.h
        TNAH/Core/Timer.h
        TNAH/Core/Timestep.h
        TNAH/Core/Utility.h
        TNAH/Core/UUID.cpp
        TNAH/Core/Window.cpp

        TNAH/Debug/Debug.h

        TNAH/Editor/EditorUI.cpp

        TNAH/Events/ApplicationEvent.h
        TNAH/Events/DebugEvent.h
        TNAH/Events/Event.h
        TNAH/Events/KeyEvent.h
        TNAH/Events/MouseEvent.h

        TNAH/Layers/ImGuiBuilder.cpp
        TNAH/Layers/ImGuiLayer.cpp
        TNAH/Layers/ImGuizmo.cpp
        TNAH/Layers/Layer.cpp
        TNAH/Layers/LayerStack.cpp
        TNAH/Layers/UI.cpp
        TNAH/Layers/ImGuiFileBrowser.cpp
        TNAH/Layers/Widgets.cpp

        TNAH/Physics/Collider.cpp
        TNAH/Physics/CollisionDetectionEngine.cpp
        TNAH/Physics/PhysicsCollision.cpp
        TNAH/Physics/PhysicsEngine.cpp
        TNAH/Physics/PhysicsEvents.cpp
        TNAH/Physics/PhysicsStructures.cpp
        TNAH/Physics/PhysicsTimestep.cpp
        TNAH/Physics/Rigidbody.cpp

        TNAH/Renderer/Animation.h
        TNAH/Renderer/AssimpGLMHelpers.h
        TNAH/Renderer/Bone.h
        TNAH/Renderer/BoneInfo.h
        TNAH/Renderer/Camera.cpp
        TNAH/Renderer/GraphicsContext.h
        TNAH/Renderer/Image.cpp
        TNAH/Renderer/Light.cpp
        TNAH/Renderer/Material.cpp
        TNAH/Renderer/Mesh.cpp
        TNAH/Renderer/RenderCommand.cpp
        TNAH/Renderer/Renderer.cpp
        TNAH/Renderer/RendererAPI.cpp
        TNAH/Renderer/RenderingBuffers.cpp
        TNAH/Renderer/Shader.cpp
        TNAH/Renderer/stb_image.h
        TNAH/Renderer/Texture.cpp
        TNAH/Renderer/VertexArray.cpp

        TNAH/Scene/GameObject.cpp
        TNAH/Scene/Scene.cpp
        TNAH/Scene/SceneCamera.cpp
        TNAH/Scene/Serializer.cpp
        TNAH/Scene/Components/Components.h
        TNAH/Scene/Components/AnimatorComponent.cpp
        TNAH/Scene/Components/AudioComponents.h
        TNAH/Scene/Components/ComponentIdentification.h
        TNAH/Scene/Components/LightComponents.h
        TNAH/Scene/Components/PhysicsComponents.cpp
        TNAH/Scene/Components/SkyboxComponent.cpp
        TNAH/Scene/Components/TerrainComponent.cpp
        TNAH/Scene/Components/AI/Actions.cpp
        TNAH/Scene/Components/AI/Affordance.cpp
        TNAH/Scene/Components/AI/AIComponent.cpp
        TNAH/Scene/Components/AI/AStar.cpp
        TNAH/Scene/Components/AI/Character.cpp
        TNAH/Scene/Components/AI/CharacterComponent.h
        TNAH/Scene/Components/AI/Emotion.cpp
        TNAH/Scene/Components/AI/EmotionComponent.cpp
        TNAH/Scene/Components/AI/PlayerInteractions.cpp
        TNAH/Scene/Components/AI/StateMachine.cpp
        TNAH/Scene/Light/DirectionalLight.cpp
        TNAH/Scene/Light/PointLight.cpp
        TNAH/Scene/Light/SpotLight.cpp

        Platform/Windows/WinInput.cpp
        Platform/Windows/WinWindow.cpp
        Platform/OpenGL/OpenGLBuffer.cpp
        Platform/OpenGL/OpenGLGraphicsContext.cpp
        Platform/OpenGL/OpenGLRendererAPI.cpp
        Platform/OpenGL/OpenGLShader.cpp
        Platform/OpenGL/OpenGLTexture.cpp
        Platform/OpenGL/OpenGLVertexArray.cpp
        Platform/IrrKlang/Klang.cpp
        )

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
