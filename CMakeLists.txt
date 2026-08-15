cmake_minimum_required(VERSION 3.20)

project(BeybladeXEngine
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(BeybladeXEngine
    src/main.cpp
    src/Combo.cpp
    src/Deck.cpp
)

target_include_directories(BeybladeXEngine
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
