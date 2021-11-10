message("vendors started")
# Library build options.
option(ASSIMP_BUILD_TESTS OFF)
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(OPTION_BUILD_TESTS OFF)
set(ASSIMP_BUILD_DRACO OFF CACHE BOOL "..." FORCE )

# Build libraries.
string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Disable compiler warnings.
add_compile_options(
        # Clang
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Wno-everything>
        # GCC
        $<$<CXX_COMPILER_ID:GNU>:-w>
        # Visual Studio
        $<$<CXX_COMPILER_ID:MSVC>:/W0>
)
message("GLM Compile Start")
add_subdirectory(glm)
message("GLM Compile Complete")

message("Assimp Compile Start")
add_subdirectory(assimp)
message("Assimp Compile Complete")

message("GLAD Compile Start")
add_subdirectory(glad)
message("GLAD Compile Complete")

message("IMGUI Compile Start")
add_subdirectory(imgui-base)
message("IMGUI Compile Complete")

message("REACTPHYSICS3D Compile Start")
add_subdirectory(reactphysics3d)
message("REACTPHYSICS3D Compile Complete")

message("IMGUIZMO Compile Start")
add_subdirectory(ImGuizmo-base)
message("IMGUIZMO Compile Complete")

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
message("GLFW Compile Start")
add_subdirectory(glfw)
message("GLFW Compile Complete")

message("SPDLOG Compile Start")
add_subdirectory(spdlog)
message("SPDLOG Compile Complete")

#option(KTX_FEATURE_VULKAN OFF)
#option(KTX_FEATURE_TESTS OFF)
#message("KTX Compile Start")
#add_subdirectory(ktx)
#message("KTX Compile Complete")

#Temp
add_subdirectory(irrklang)

set_target_properties(reactphysics3d PROPERTIES ENABLE_EXPORTS ON)
set_target_properties(reactphysics3d PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Puts a stop to the endlessly irritating practise postfixing 'd' onto debug libraries.
set_target_properties(assimp PROPERTIES DEBUG_POSTFIX "")
set_target_properties(glfw PROPERTIES DEBUG_POSTFIX "")
set_target_properties(glad PROPERTIES DEBUG_POSTFIX "")
set_target_properties(reactphysics3d PROPERTIES DEBUG_POSTFIX "")

# Ignore warnings from library headers.
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
        glfw/include
        glfw/src
        glad/include
        glad/src
        assimp/include
        reactphysics3d/include
        imgui-base/imgui
        imgui-base/imgui/backends
        ImGuizmo-base/ImGuizmo
        spdlog/include
        glm
        entt/src
        ktx/include
        miniaudio
        irrklang/include
        )
message("vendors ended")