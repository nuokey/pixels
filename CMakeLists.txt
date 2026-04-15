cmake_minimum_required(VERSION 3.22)
project(MySFMLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим SFML 3 с правильными именами компонентов (с заглавной буквы!)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(main main.cpp)

# Линкуем с правильными именами целей (с префиксом SFML::)
target_link_libraries(main PRIVATE 
    SFML::Graphics
    SFML::Window 
    SFML::System
)