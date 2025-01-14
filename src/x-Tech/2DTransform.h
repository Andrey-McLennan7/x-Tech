#pragma once

#ifndef X_TECH_2D_TRANSFORM_H
#define X_TECH_2D_TRANSFORM_H

#include "Component.h"

namespace xTech
{
	class Transform2D : public Component
	{
	// Private data members
	private:

		glm::vec2 m_position;

		float m_rotation;
		float m_scale;

	// Public member functions
	public:

		virtual void on_initialize() override;

		void move(const glm::vec2& move);

		void position(const glm::vec2& position);
		glm::vec2 position() const;

		void rotation(float rotation);
		float rotation() const;

		void scale(float scale);
		float scale() const;
	};
}

#endif