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
#include "Mouse.h"
#include "Keycode.h"
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

#endif