cmake_minimum_required(VERSION 4.4.5) #CMake 4.4.5
set(CMAKE_CXX_STANDARD 17) #C++17

set(PROJECT_NAME "LAND_OUT")

#Проект
project(${PROJECT_NAME} VERSION 1.0.0)

#Системный пакет glfw
find_package(glfw3)

#Основные файлы исходного кода
add_executable(${PROJECT_NAME} src/config.h src/main.cpp)

#линовка GLFW к проекту
target_include_directories(${PROJECT_NAME} PRIVATE dependencies) #Папка с hpp GLFW
target_link_directories(${PROJECT_NAME} PRIVATE lib) # Папка основной библиотеки msys2
target_link_libraries(${PROJECT_NAME} glfw3 glad) # Линковка библиотеки

#Установка настроек для GLFW относительно проекта
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/glad)
target_link_libraries(${PROJECT_NAME} glad)
