cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(X-TECH)

if(WIN32)

	add_definitions(-DGLEW_STATIC -DSDL_MAIN_HANDLED)

	include_directories(
		src
		contrib/cl-windows-x86_64/include
		contrib/include
	)

	link_directories(
		contrib/cl-windows-x86_64/lib
	)

	set(LIBOPENAL OpenAL32)
	set(LIBOPENGL opengl32)
	set(LIBGLEW	   glew32s)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")

	include_directories(
		src
  		contrib/emcc-emscripten-wasm/include
		contrib/include
	)

	link_directories(
		contrib/emcc-emscripten-wasm/lib
	)

	set(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(CMAKE_CXX_FLAGS "-sNO_DISABLE_EXCEPTION_CATCHING")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ${CMAKE_SOURCE_DIR}/res@res")

	set(LIBOPENAL openal)
	set(LIBOPENGL     GL)
	set(LIBGLEW	    GLEW)

endif()

add_library(rend
	src/rend/rend.h
	src/rend/Shader.h
	src/rend/Shader.cpp
	src/rend/Texture.h
	src/rend/Texture.cpp
	src/rend/stb_image.h
	src/rend/Model.h
	src/rend/Model.cpp
	src/rend/Mesh.h
	src/rend/Mesh.cpp
	src/rend/Shape.h
	src/rend/Shape.cpp
	src/rend/Triangle.h
	src/rend/Triangle.cpp
	src/rend/Pyramid.h
	src/rend/Pyramid.cpp
	src/rend/Quad.h
	src/rend/Quad.cpp
	src/rend/Cube.h
	src/rend/Cube.cpp
	src/rend/Font.h
	src/rend/Font.cpp
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
	src/x-Tech/2DTransform.h
	src/x-Tech/2DTransform.cpp
	src/x-Tech/Window.h
	src/x-Tech/Window.cpp
	src/x-Tech/Shader.h
	src/x-Tech/Shader.cpp
	src/x-Tech/TriangleRenderer.h
	src/x-Tech/TriangleRenderer.cpp
	src/x-Tech/Resource.h
	src/x-Tech/Resource.cpp
	src/x-Tech/Cache.h
	src/x-Tech/Cache.cpp
	src/x-Tech/Texture.h
	src/x-Tech/Texture.cpp
	src/x-Tech/Audio.h
	src/x-Tech/Audio.cpp
	src/x-Tech/SoundSource.h
	src/x-Tech/SoundSource.cpp
	src/x-Tech/Collider.h
	src/x-Tech/Collider.cpp
	src/x-Tech/BoxCollider.h
	src/x-Tech/BoxCollider.cpp
	src/x-Tech/SphereCollider.h
	src/x-Tech/SphereCollider.cpp
	src/x-Tech/RigidBody.h
	src/x-Tech/RigidBody.cpp
	src/x-Tech/Input.h
	src/x-Tech/Input.cpp
	src/x-Tech/KeyCode.h
	src/x-Tech/MouseCode.h
	src/x-Tech/ControllerCode.h
	src/x-Tech/Model.h
	src/x-Tech/Model.cpp
	src/x-Tech/ModelRenderer.h
	src/x-Tech/ModelRenderer.cpp
	src/x-Tech/Camera.h
	src/x-Tech/Camera.cpp
	src/x-Tech/ShapeRenderer.h
	src/x-Tech/ShapeRenderer.cpp
	src/x-Tech/Shape.h
	src/x-Tech/Shape.cpp
	src/x-Tech/PointLight.h
	src/x-Tech/PointLight.cpp
	src/x-Tech/InputDevice.h
	src/x-Tech/InputDevice.cpp
	src/x-Tech/Keyboard.h
	src/x-Tech/Keyboard.cpp
	src/x-Tech/Mouse.h
	src/x-Tech/Mouse.cpp
	src/x-Tech/Controller.h
	src/x-Tech/Controller.cpp
	src/x-Tech/Font.h
	src/x-Tech/Font.cpp
	src/x-Tech/2DGuiRenderer.h
	src/x-Tech/2DGuiRenderer.cpp
)

target_link_libraries(rend SDL2 ${LIBGLEW} ${LIBOPENGL} ${LIBOPENAL} assimp-vc143-mtd freetype)

target_link_libraries(x-Tech rend)

add_executable(demo
	src/demo/main.cpp
	src/demo/Data.h
	src/demo/Data.cpp
	src/demo/Controls.h
	src/demo/Controls.cpp
	src/demo/Shoot.h
	src/demo/Shoot.cpp
	src/demo/Movement.h
	src/demo/Movement.cpp
)

target_link_libraries(demo x-Tech)