#pragma once
#include "Collider.h"

namespace xTech
{
	class SphereCollider : public Collider
	{
	// Private data members
	private:

		float m_radius;

	// Public member functions
	public:

		virtual void on_initialize() override;

		virtual bool on_collision(const Collider& other) const override;
		virtual void get_collision_response(const Collider& other) const override;

		void radius(float radius);
	};
}