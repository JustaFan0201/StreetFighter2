cmake_minimum_required(VERSION 3.16)
project(StreetFighter2)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    ptsd

    URL         https://github.com/ntut-open-source-club/practical-tools-for-simple-design/archive/refs/tags/v0.2.zip

    # Or alternatively if you want to use a specific git commit instead of a release:
    # GIT_REPOSITORY  https://github.com/ntut-open-source-club/practical-tools-for-simple-design.git
    # GIT_TAG         <git_tag>

    SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/PTSD
)

FetchContent_MakeAvailable(ptsd)

include(files.cmake)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR}/)
list(TRANSFORM INCLUDE_FILES PREPEND ${INCLUDE_DIR}/)

# file(GLOB_RECURSE SRC_FILES src/*)
# file(GLOB_RECURSE HEADER_FILES include/*)

add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
        ${SRC_FILES}
            src/Scenes/Scene.cpp
            src/Scenes/StartScene.cpp
            src/Scenes/SceneManager.cpp
            src/Scenes/SlectScene.cpp
            src/Scenes/PassScene.cpp
            src/Scenes/BattleScene.cpp

            include/Others/FighterInfo.hpp
            include/Others/Camera.hpp
            include/Others/Bloodstick.hpp
            include/Others/Controller.hpp

            src/Fighters/Fighter.cpp
            src/Fighters/Ken.cpp
            src/Fighters/Ryu.cpp
            src/Fighters/Chunli.cpp
            src/Fighters/Blanka.cpp
            src/Fighters/Honda.cpp
            src/Fighters/Guile.cpp
            src/Fighters/Dhalsim.cpp
            src/Fighters/Zangief.cpp

        ${HEADER_FILES}
            include/ImageSpace.hpp
            include/AnimationSpace.hpp
            include/Word.hpp

            include/Scenes/Scene.hpp
            include/Scenes/StartScene.hpp
            include/Scenes/SceneManager.hpp
            include/Scenes/SlectScene.hpp
            include/Scenes/PassScene.hpp
            include/Scenes/BattleScene.hpp

            src/Others/Camera.cpp
            src/Others/Bloodstick.cpp

            include/Fighters/Fighter.hpp
            include/Fighters/Ken.hpp
            include/Fighters/Ryu.hpp
            include/Fighters/Chunli.hpp
            include/Fighters/Blanka.hpp
            include/Fighters/Honda.hpp
            include/Fighters/Guile.hpp
            include/Fighters/Dhalsim.hpp
            include/Fighters/Zangief.hpp

)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")
else()
    message(FATAL_ERROR "relative RESOURCE_DIR is WIP, Please use `-DCMAKE_BUILD_TYPE=Debug` build for now.")
    # target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_INSTALL_PREFIX}/Resources")
endif()

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${DEPENDENCY_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2main
    PTSD
)
