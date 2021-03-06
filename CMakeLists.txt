# Set cmake minimum version.
set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_minimum_required(VERSION 3.16)
if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif(APPLE)
# Set the project details.
set(PROJECT_NAME TNAH)
project(${PROJECT_NAME} LANGUAGES CXX C)

# If enabled, the post build symlink will copy instead.
option(CopyResources "CopyResources" ON)

# Clang sanitizer settings.
set(SANITIZER_OS "Darwin,Linux")
set(SANITIZER_FLAGS "-fsanitize=address,undefined,leak")

# Treat warnings as errors.
option(WarningsAsErrors "WarningsAsErrors" OFF)

# Disable in-source builds.
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

# Disable debug library postfix.
set(CMAKE_DEBUG_POSTFIX "")

# Set build type to debug by default.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add Linux flag.
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

set(BUILD_OUTPUT ${PROJECT_SOURCE_DIR}/bin)
message(${BUILD_OUTPUT})
# Set build output directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT}/vendor)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT}/vendor)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${BUILD_OUTPUT})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${BUILD_OUTPUT})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG    ${BUILD_OUTPUT}/vendor)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${BUILD_OUTPUT}/vendor)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG    ${BUILD_OUTPUT}/vendor)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${BUILD_OUTPUT}/vendor)

add_compile_definitions(TNAH_PLATFORM_WINDOWS)

# Define the Library.
add_library(${PROJECT_NAME} SHARED)

# Set C++ standard.
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )

# Find dependencies.
find_package(OpenGL REQUIRED)

# Build 3rd Party Libraries
add_subdirectory(vendor)

# Define source files.
add_subdirectory(core)

# Remove the default warning level from MSVC.
if (MSVC)
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# Treat warnings as errors if enabled.
if (WarningsAsErrors)
    target_compile_options(${PROJECT_NAME} PUBLIC
            $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Werror>
            $<$<CXX_COMPILER_ID:MSVC>:/WX>
            )
endif()
# Set compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC
        # Clang
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Weverything -fcolor-diagnostics
        # Disable specific warnings.
        -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
        -Wno-deprecated-declarations -Wno-exit-time-destructors
        -Wno-switch-enum -Wno-weak-vtables -Wno-global-constructors>
        # GCC
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always>
        # Visual Studio
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        # Enable the clang sanitizer.
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:${SANITIZER_OS}>>:${SANITIZER_FLAGS}>
        )

# Link against the clang sanitizer.
target_link_options(${PROJECT_NAME} PUBLIC
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:${SANITIZER_OS}>>:${SANITIZER_FLAGS}>
        )
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE 1)




# Include and link against dependencies.
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL glfw glad assimp glm reactphysics3d spdlog imgui imguizmo)

#target_link_libraries(EntryPoint PUBLIC TNAH)