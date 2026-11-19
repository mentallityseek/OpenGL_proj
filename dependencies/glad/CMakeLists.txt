# Указание минимальной версии для Cmake для GLAD
cmake_minimum_required(VERSION 4.4.5 FATAL_ERROR)
project(Glad C)

#Создание и линковка библиотеки к glad.c 
add_library(glad STATIC include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include)

