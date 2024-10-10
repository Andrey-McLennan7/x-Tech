cmake_minimum_required(VERSION ${CMAKE_VERSION})

project(X-TECH)

include_directories(
	src
	contrib
	contrib/cl-windows-x64/SDL2/include
)

link_directories(
	src
	contrib/cl-windows-x64/SDL2/lib
)

add_library(x-Tech
	src/x-Tech/x-Tech.h
	src/x-Tech/Core.cpp
	src/x-Tech/Core.h
	src/x-Tech/Entity.h
	src/x-Tech/Entity.cpp
	src/x-Tech/Component.h
	src/x-Tech/Component.cpp
)

add_executable(demo
	src/demo/main.cpp
)

target_link_libraries(demo x-Tech)