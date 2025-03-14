cmake_minimum_required(VERSION 3.28)
project(moss-engine LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Fetch SFML
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Fetch IMGUI
FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.90.4 # Latest stable as of March 2025
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(imgui)

# Fetch ImGui-SFML (manual population)
FetchContent_Declare(imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v2.6 # Matches SFML 2.6.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_GetProperties(imgui-sfml)
if(NOT imgui-sfml_POPULATED)
    FetchContent_Populate(imgui-sfml)
    add_library(ImGui-SFML STATIC
        ${imgui-sfml_SOURCE_DIR}/imgui-SFML.cpp
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp "src/systems/SpriteRenderSystem.h"  "src/utils/TextureManager.h" "src/utils/TextureManager.cpp" "src/utils/Camera.h" "src/utils/Camera.cpp" "src/utils/Logger.h" "src/utils/Logger.cpp" "src/utils/ConsoleColor.h" "src/components/PositionComponent.h" "src/components/VelocityComponent.h" "src/components/SpriteRenderComponent.h" "src/components/RigidbodyComponent.h" "src/components/CollisionComponent.h")
    target_include_directories(ImGui-SFML PUBLIC
        ${imgui-sfml_SOURCE_DIR}
        ${imgui_SOURCE_DIR}
    )
    target_link_libraries(ImGui-SFML PUBLIC sfml-graphics sfml-window sfml-system)
    target_compile_definitions(ImGui-SFML PUBLIC IMGUI_USER_CONFIG="${imgui_SOURCE_DIR}/imconfig.h")
endif()

add_executable(${PROJECT_NAME} 
    "src/Main.cpp" 
    "src/core/Component.h" 
    "src/core/ComponentPool.h"  
    "src/core/Entity.h" 
    "src/core/World.h" 
    "src/core/ComponentPoolBase.h" 
    "src/core/System.h"  
    "src/systems/MovementSystem.h"   
    "src/systems/CollisionSystem.h" 
    "src/systems/CollisionSystem.cpp" 
    "src/core/World.cpp" 
    "src/systems/SpriteRenderSystem.h"  
    "src/utils/TextureManager.h" 
    "src/utils/TextureManager.cpp" 
    "src/utils/Camera.h" 
    "src/utils/Camera.cpp" 
    "src/utils/Logger.h" 
    "src/utils/Logger.cpp" 
    "src/utils/ConsoleColor.h" "src/components/PositionComponent.h" "src/components/VelocityComponent.h" "src/components/SpriteRenderComponent.h" "src/components/RigidbodyComponent.h" "src/components/CollisionComponent.h")

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics ImGui-SFML)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()