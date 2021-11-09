project(glad LANGUAGES C)

add_library(glad STATIC
        include/glad/gl.h
        include/glad/egl.h
        include/glad/glx.h
        include/glad/wgl.h
        include/glad/vulkan.h
        include/vk_platform.h
        include/EGL/eglplatform.h
        include/KHR/khrplatform.h
        src/gl.c
        src/egl.c
        src/glx.c
        src/wgl.c
        src/vulkan.c
        )

target_compile_options(glad PRIVATE -fPIC)

target_include_directories(glad PUBLIC include/)