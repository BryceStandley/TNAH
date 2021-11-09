project(imguizmo)

add_library(imguizmo STATIC)

target_sources(imguizmo PRIVATE
        ImGuizmo/GraphEditor.cpp
        ImGuizmo/ImCurveEdit.cpp
        ImGuizmo/ImGradient.cpp
        ImGuizmo/ImGuizmo.cpp
        ImGuizmo/ImSequencer.cpp
        )

target_compile_options(imguizmo PRIVATE -fPIC)

target_include_directories(imguizmo PUBLIC . include)
target_link_libraries(imguizmo PRIVATE imgui ${APP_SERVICES_LIBRARY} ${COCOA_LIBRARY})