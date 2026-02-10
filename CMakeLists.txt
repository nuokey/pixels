cmake_minimum_required(VERSION 3.10)
project(MySFMLProject)

set(CMAKE_CXX_STANDARD 17)

# Поиск SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(main main.cpp)

# Подключение SFML
target_link_libraries(main SFML::Graphics SFML::Window SFML::System)