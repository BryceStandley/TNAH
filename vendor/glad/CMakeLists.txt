project(glad LANGUAGES C)

add_library(glad STATIC
        include/glad/glad.h
        include/KHR/khrplatform.h
        glad.c
        )

target_compile_options(glad PRIVATE -fPIC)

target_include_directories(glad PUBLIC include/)