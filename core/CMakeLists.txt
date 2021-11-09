target_precompile_headers(${PROJECT_NAME} PRIVATE
        src/tnahpch.h
        )

# Add source files.
target_sources(${PROJECT_NAME}
        PRIVATE
            src/TNAH/Audio/Audio.cpp
            src/TNAH/Audio/AudioAPI.cpp

            src/TNAH/Core/AABB.h
            src/TNAH/Core/Application.cpp
            src/TNAH/Core/Buffer.h
            src/TNAH/Core/Core.h
            src/TNAH/Core/EntryPoint.h
            src/TNAH/Core/FileManager.cpp
            src/TNAH/Core/FileStructures.h
            src/TNAH/Core/Input.h
            src/TNAH/Core/KeyCodes.h
            src/TNAH/Core/Log.cpp
            src/TNAH/Core/Math.cpp
            src/TNAH/Core/MouseCodes.h
            src/TNAH/Core/Ref.cpp
            src/TNAH/Core/Singleton.h
            src/TNAH/Core/Timer.h
            src/TNAH/Core/Timestep.h
            src/TNAH/Core/Utility.h
            src/TNAH/Core/UUID.cpp
            src/TNAH/Core/Window.cpp

            src/TNAH/Debug/Debug.h

            src/TNAH/Editor/EditorUI.cpp

            src/TNAH/Events/ApplicationEvent.h
            src/TNAH/Events/DebugEvent.h
            src/TNAH/Events/Event.h
            src/TNAH/Events/KeyEvent.h
            src/TNAH/Events/MouseEvent.h

            src/TNAH/Layers/ImGuiBuilder.cpp
            src/TNAH/Layers/ImGuiLayer.cpp
            src/TNAH/Layers/ImGuizmo.cpp
            src/TNAH/Layers/Layer.cpp
            src/TNAH/Layers/LayerStack.cpp
            src/TNAH/Layers/UI.cpp

            src/TNAH/Physics/Collider.cpp
            src/TNAH/Physics/CollisionDetectionEngine.cpp
            src/TNAH/Physics/PhysicsCollision.cpp
            src/TNAH/Physics/PhysicsEngine.cpp
            src/TNAH/Physics/PhysicsEvents.cpp
            src/TNAH/Physics/PhysicsStructures.cpp
            src/TNAH/Physics/PhysicsTimestep.cpp
            src/TNAH/Physics/Rigidbody.cpp

            src/TNAH/Renderer/Animation.h
            src/TNAH/Renderer/AssimpGLMHelpers.h
            src/TNAH/Renderer/Bone.h
            src/TNAH/Renderer/BoneInfo.h
            src/TNAH/Renderer/Camera.cpp
            src/TNAH/Renderer/GraphicsContext.h
            src/TNAH/Renderer/Image.cpp
            src/TNAH/Renderer/Light.cpp
            src/TNAH/Renderer/Material.cpp
            src/TNAH/Renderer/Mesh.cpp
            src/TNAH/Renderer/RenderCommand.cpp
            src/TNAH/Renderer/Renderer.cpp
            src/TNAH/Renderer/RendererAPI.cpp
            src/TNAH/Renderer/RenderingBuffers.cpp
            src/TNAH/Renderer/Shader.cpp
            src/TNAH/Renderer/stb_image.h
            src/TNAH/Renderer/Texture.cpp
            src/TNAH/Renderer/VertexArray.cpp

            src/TNAH/Scene/GameObject.cpp
            src/TNAH/Scene/Scene.cpp
            src/TNAH/Scene/SceneCamera.cpp
            src/TNAH/Scene/Serializer.cpp
            src/TNAH/Scene/Components/Components.h
            src/TNAH/Scene/Components/AnimatorComponent.cpp
            src/TNAH/Scene/Components/AudioComponents.h
            src/TNAH/Scene/Components/ComponentIdentification.h
            src/TNAH/Scene/Components/LightComponents.h
            src/TNAH/Scene/Components/PhysicsComponents.cpp
            src/TNAH/Scene/Components/SkyboxComponent.cpp
            src/TNAH/Scene/Components/TerrainComponent.cpp
            src/TNAH/Scene/Components/AI/Actions.cpp
            src/TNAH/Scene/Components/AI/Affordance.cpp
            src/TNAH/Scene/Components/AI/AIComponent.cpp
            src/TNAH/Scene/Components/AI/AStar.cpp
            src/TNAH/Scene/Components/AI/Character.cpp
            src/TNAH/Scene/Components/AI/CharacterComponent.h
            src/TNAH/Scene/Components/AI/Emotion.cpp
            src/TNAH/Scene/Components/AI/EmotionComponent.cpp
            src/TNAH/Scene/Components/AI/PlayerInteractions.cpp
            src/TNAH/Scene/Components/AI/StateMachine.cpp
            src/TNAH/Scene/Light/DirectionalLight.cpp
            src/TNAH/Scene/Light/PointLight.cpp
            src/TNAH/Scene/Light/SpotLight.cpp

            src/Platform/Windows/WinInput.cpp
            src/Platform/Windows/WinWindow.cpp
            src/Platform/OpenGL/OpenGLBuffer.cpp
            src/Platform/OpenGL/OpenGLGraphicsContext.cpp
            src/Platform/OpenGL/OpenGLRendererAPI.cpp
            src/Platform/OpenGL/OpenGLShader.cpp
            src/Platform/OpenGL/OpenGLTexture.cpp
            src/Platform/OpenGL/OpenGLVertexArray.cpp
            src/Platform/IrrKlang/Klang.cpp
        )

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
