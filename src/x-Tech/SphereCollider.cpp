#include "SphereCollider.h"
#include "Transform.h"

#include <glm/glm.hpp>

namespace xTech
{
	void SphereCollider::on_initialize()
	{
		this->m_radius = 1.0f;
	}

	bool SphereCollider::on_collision(const Collider& other) const
	{
		const SphereCollider* _other{ (const SphereCollider*)&other };

		glm::vec3 a{ this->transform()->position()};
		glm::vec3 b{ _other->transform()->position()};

		float ar{ this->m_radius };
		float br{ _other->m_radius };

		if (glm::vec3{ b - a }.length() > (ar + br))
		{
			return false;
		}

		return true;
	}

	void SphereCollider::get_collision_response(const Collider& other) const
	{
		float amount{ 0.1f };
		float step{ 0.1f };
	}

	void SphereCollider::radius(float radius)
	{
		this->m_radius = radius;
	}
}