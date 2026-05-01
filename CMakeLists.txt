cmake_minimum_required(VERSION 3.22)
project(pixels)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим SFML 3 с правильными именами компонентов (с заглавной буквы!)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# Линкуем с правильными именами целей (с префиксом SFML::)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SFML::Graphics
    SFML::Window 
    SFML::System
)