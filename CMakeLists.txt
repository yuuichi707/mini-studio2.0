cmake_minimum_required(VERSION 3.16)
project(mini-Studio2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

add_executable(Mini-Studio2.0
        mini-Studio2.0/mini-Studio2.0/mini-Studio2.0.cpp
        mini-Studio2.0/mini-Studio2.0/player.cpp
        mini-Studio2.0/mini-Studio2.0/entity.cpp
)

target_link_libraries(mini-Studio2.0
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
)