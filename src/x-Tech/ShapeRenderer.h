#pragma once

#ifndef X_TECH_SHAPE_RENDERER_H
#define X_TECH_SHAPE_RENDERER_H

#include "Component.h"

namespace xTech
{
	class Shader;
	class Shape;

	class ShapeRenderer : public Component
	{
	// Private data members
	private:

		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<Shape> m_shape;

		glm::vec3 m_colour;

	// Public member functions
	public:

		virtual void on_initialize() override;
		virtual void on_display() override;

		void shader(const std::string& path);
		void shader(std::shared_ptr<Shader> shader);

		void shape(const std::string& path);
		void shape(std::shared_ptr<Shape> shape);

		void colour(const glm::vec3& colour);
		glm::vec3 colour() const;
	};
}

#endif