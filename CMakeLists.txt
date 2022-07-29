cmake_minimum_required(VERSION 3.21.4)

project(AutomataEngine)

add_executable(${PROJECT_NAME} 
    ./src/main.cpp
    ./src/Automata/Automata.h
    ./src/Automata/Core/Core.h
    ./src/Automata/Core/Application.cpp
    ./src/Automata/Core/Layer.cpp
    ./src/Automata/Core/LayerStack.cpp
    ./src/Automata/Core/ImGui/ImGuiBuild.cpp
    ./src/Automata/Core/ImGui/ImGuiLayer.cpp
    ./src/Automata/Core/Cell.h
    ./src/Automata/Core/CellMatrix.cpp
    ./src/Automata/Core/Elements/Element.cpp
    ./src/Automata/Core/Elements/Solids/Sand.cpp
    ./src/Automata/Core/Elements/Liquids/Water.cpp
    ./src/Automata/Core/Elements/Gases/Smoke.cpp
    ./src/Automata/Renderer/Shader.cpp
    ./src/Automata/Renderer/Camera.cpp
    ./src/Automata/Renderer/Mesh.cpp
    ./src/Automata/Renderer/Model.cpp
    ./src/Automata/Renderer/AutomataRenderer.cpp
    )
add_subdirectory(./dependencies/glad)
add_subdirectory(./dependencies/glm)
add_subdirectory(./dependencies/imgui)

target_include_directories(${PROJECT_NAME} 
    PRIVATE ./dependencies
    PRIVATE ./dependencies/GLFW/include
    PRIVATE ./dependencies/glad/include
    PRIVATE ./dependencies/assimp/include
    PRIVATE ./dependencies/glm
    PRIVATE ./dependencies/imgui
    PRIVATE ./src/Automata
    PRIVATE ./src/Automata/Core
    PUBLIC  ./src/Automata/Core/Elements
    )

target_precompile_headers(${PROJECT_NAME}
    PRIVATE src/Automata/atpch.h)

target_link_directories(${PROJECT_NAME} 
    PRIVATE ./dependencies/GLFW/lib
    PRIVATE ./dependencies/assimp/lib)

target_link_libraries(${PROJECT_NAME}
    PRIVATE glad
    PRIVATE glm
    PRIVATE glfw3
    PRIVATE imgui
    PRIVATE assimp-vc142-mtd
    PRIVATE opengl32
    )
# move dlls
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/dependencies/assimp/lib/assimp-vc142-mtd.dll"
    ${PROJECT_BINARY_DIR}
    COMMENT "Copying dll to binary folder"
)

# copy resources
add_custom_target(
    copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${PROJECT_SOURCE_DIR}/resources
    ${PROJECT_BINARY_DIR}/resources
    COMMENT "Copying Resources Into binary folder"
    )

add_dependencies(${PROJECT_NAME} copy_resources)

#add_compile_definitions(_APPLE_)