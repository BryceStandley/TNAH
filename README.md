![TNAH-Logo](/resources/logo/logo.png)

# TNAH
[![Build Status](https://github.com/BryceStandley/TNAH/workflows/Windows/badge.svg)](https://github.com/BryceStandley/TNAH/actions/workflows/Windows.yml)
[![Build Status](https://github.com/BryceStandley/TNAH/workflows/Mac/badge.svg)](https://github.com/BryceStandley/TNAH/actions/workflows/Windows.yml)
[![Build Status](https://github.com/BryceStandley/TNAH/workflows/Linux/badge.svg)](https://github.com/BryceStandley/TNAH/actions/workflows/Windows.yml)
The TNAH is a game engine written in C++ targeting OpenGL 4.6. The TNAH name stands for **T**eam **N**ames **A**re **H**ard. 
The name is a continuation of our group name during the development of the engine for university.

## History
This project originally started development in early 2021 as a university project but has since become a passion project moving forward.
To view the original version of this engine visit the original git --> [TNAH-Engine](https://github.com/BryceStandley/TNAH-Engine)

## Wiki
Visit the [wiki](https://github.com/BryceStandley/TNAH/wiki) to read up on example applications!
You can also visit our [documentation](https://github.com/BryceStandley/TNAH) to view our [Doxygen](https://www.doxygen.nl/index.html) output.

## LFS
Ensure git lfs is installed on your system prior to cloning.
```git lfs install```

## Cloning
``` git clone https://github.com/BryceStandley/TNAH.git```
``` cd TNAH ```

### Optional
If you would like to use the most up-to-date version of the engine, use:
``` git checkout dev```
or the default main branch will be used.

### Sub-modules
TNAH uses sub-modules for its dependencies, use:
``` git submodule update --init --recursive --depth 1 ```

## Building
Cmake is used to build the engine and its modules.
### TODO -- Add cmake instructions
#### Windows
#### Mac
#### Linux
## Work In Progress
The TNAH engine is an ongoing development project which will see additions of may different components and models.

## Dependencies
- Assimp (3D mesh loading) [Git](https://github.com/assimp/assimp)
- Entt (Entity Component System) [Git](https://github.com/skypjack/entt)
- GLFW (OpenGl Window Management) [Git](https://github.com/glfw/glfw)
- GLM (3D Math Library) [Git](https://github.com/g-truc/glm)
- ImGui (GUI Library) [Git](https://github.com/ocornut/imgui)
- ImGuizmo (Gizmo ImGui Addon) [Git](https://github.com/CedricGuillemet/ImGuizmo)
- KTX-Software (KTX(1 and 2) Texture Loader) [Git](https://github.com/KhronosGroup/KTX-Software)
- Miniaudio (2D Audio Library) [Git](https://github.com/mackron/miniaudio)
- ReactPhysics3D (3D Physics and Collision Library) [Git](https://github.com/DanielChappuis/reactphysics3d)
- SPDLOG (Logger) [Git](https://github.com/gabime/spdlog)

## License
This project is licensed under the MIT license. Please refer to the [License](/LICENSE) file for details.