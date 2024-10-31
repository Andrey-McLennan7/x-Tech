cmake_minimum_required(VERSION ${CMAKE_VERSION})

project(X-TECH)

add_definitions(
	-DGLEW_STATIC
)

include_directories(
	src
	contrib/cl-windows-x86_64/include
	contrib/include
)

link_directories(
	contrib/cl-windows-x86_64/lib
)

add_library(rend
	src/rend/rend.h
	src/rend/Shader.h
	src/rend/Shader.cpp
)

add_library(x-Tech
	src/x-Tech/x-Tech.h
	src/x-Tech/Core.cpp
	src/x-Tech/Core.h
	src/x-Tech/Entity.h
	src/x-Tech/Entity.cpp
	src/x-Tech/Component.h
	src/x-Tech/Component.cpp
	src/x-Tech/Debug.h
	src/x-Tech/Debug.cpp
	src/x-Tech/Transform.h
	src/x-Tech/Transform.cpp
	src/x-Tech/Window.h
	src/x-Tech/Window.cpp
)

target_link_libraries(rend SDL2 glew32s opengl32)

target_link_libraries(x-Tech rend)

add_executable(demo
	src/demo/main.cpp
)

target_link_libraries(demo x-Tech)