cmake_minimum_required(VERSION 3.20.0)

add_subdirectory(bluetooth)
add_subdirectory(sensor)

target_sources(app PRIVATE main.c)
