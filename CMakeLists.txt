cmake_minimum_required(VERSION ${CMAKE_VERSION})

project(X-TECH)

include_directories(
	src
)

add_library(x-Tech
	src/x-Tech/dummy.cpp
	src/x-Tech/dummy.h
)

add_executable(demo
	src/demo/main.cpp
)

target_link_libraries(demo x-Tech)