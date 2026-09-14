cmake_minimum_required(VERSION 3.20)

project(BeybladeXEngine
    VERSION 1.0
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(BeybladeXEngine
    src/main.cpp
    src/combo.cpp
    src/deck.cpp
    src/database.cpp
)

target_include_directories(BeybladeXEngine
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

include(FetchContent)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
if(UNIX AND NOT APPLE)
    set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
endif()

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
)

FetchContent_MakeAvailable(glfw glm)

add_library(glad STATIC
    third_party/glad/src/gl.c
)

target_include_directories(glad
    PUBLIC
        ${PROJECT_SOURCE_DIR}/third_party/glad/include
)

