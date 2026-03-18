cmake_minimum_required(VERSION 3.16)

project(mini_studio2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

file(GLOB_RECURSE SRC_FILES
        mini-studio2.0/*.cpp
)

add_executable(mini_studio2 ${SRC_FILES})

target_link_libraries(mini_studio2
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
)