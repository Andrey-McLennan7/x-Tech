#pragma once

#ifndef X_TECH_H
#define X_TECH_H

bool windows

#ifdef _WIN32
= true;
#else
= false;
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace xTech
{
	using namespace glm;
}

#include <GL/glew.h>

#include "Core.h"
#include "Entity.h"
#include "Component.h"
#include "Debug.h"
#include "Transform.h"
#include "Window.h"
#include "Input.h"
#include "KeyCode.h"
#include "MouseCode.h"
#include "ControllerCode.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
#include "TriangleRenderer.h"
#include "Resource.h"
#include "Cache.h"
#include "Texture.h"
#include "Shader.h"
#include "Audio.h"
#include "SoundSource.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Model.h"
#include "ModelRenderer.h"
#include "Camera.h"
#include "Shape.h"
#include "ShapeRenderer.h"
#include "PointLight.h"
#include "2DGuiRenderer.h"
#include "Font.h"

#endif