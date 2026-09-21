cmake_minimum_required(VERSION 3.20)

project(BeybladeXEngine
    VERSION 1.0
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
# Existing CRUD app (combos / decks)
# ---------------------------------------------------------------------------
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

# ---------------------------------------------------------------------------
# Third-party dependencies for the physics sim / renderer
# ---------------------------------------------------------------------------
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

# GLAD is vendored (pre-generated for GL 3.3 core, no extensions) rather than
# fetched, since generation depends on the Khronos registry rather than a
# straightforward git checkout. Regenerate under third_party/glad if a newer
# GL feature set is needed later.
add_library(glad STATIC
    third_party/glad/src/gl.c
)

target_include_directories(glad
    PUBLIC
        ${PROJECT_SOURCE_DIR}/third_party/glad/include
)

# ---------------------------------------------------------------------------
# Physics sim executable
# ---------------------------------------------------------------------------
add_executable(BeybladeSim
    src/sim_main.cpp
    src/render/window.cpp
    src/render/shader.cpp
)

target_include_directories(BeybladeSim
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(BeybladeSim
    PRIVATE
        glfw
        glad
        glm::glm
)

# Copy shaders next to the sim binary so relative paths work from the build dir.
add_custom_command(TARGET BeybladeSim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:BeybladeSim>/shaders
)
