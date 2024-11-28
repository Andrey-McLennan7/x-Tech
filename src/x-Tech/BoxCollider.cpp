#include "BoxCollider.h"
#include "Transform.h"

namespace xTech
{
	void BoxCollider::on_initialize()
	{
		this->m_size = glm::vec3{ 1.0f };
		this->m_offset = glm::vec3{ this->m_size / 2.0f };
	}

	bool BoxCollider::on_collision(const Collider& other) const
	{
		const BoxCollider* _other = (const BoxCollider*)&other;

		glm::vec3 a{ this->transform()->m_position };
		glm::vec3 b{ _other->transform()->m_position };

		glm::vec3 ahs{ this->m_offset };
		glm::vec3 bhs{ _other->m_offset };

		// Detect interseption with x
		if (a.x > b.x)
		{
			if (b.x + bhs.x < a.x - ahs.x)
			{
				return false;
			}
		}
		else
		{
			if (a.x + ahs.x < b.x - bhs.x)
			{
				return false;
			}
		}

		// Detect interseption with y
		if (a.y > b.y)
		{
			if (b.y + bhs.y < a.y - ahs.y)
			{
				return false;
			}
		}
		else
		{
			if (a.y + ahs.y < b.y - bhs.y)
			{
				return false;
			}
		}

		// Detect interseption with z
		if (a.z > b.z)
		{
			if (b.z + bhs.z < a.z - ahs.z)
			{
				return false;
			}
		}
		else
		{
			if (a.z + ahs.z < b.z - bhs.z)
			{
				return false;
			}
		}

		return true;
	}

	void BoxCollider::get_collision_response(const Collider& other) const
	{
		float amount{ 0.1f };
		float step{ 0.1f };

		glm::vec3& position{ this->transform()->m_position };

		while (true)
		{
			if (!this->on_collision(other)) break;
			position.x += amount;

			if (!this->on_collision(other)) break;
			position.x -= amount;
			position.x -= amount;

			if (!this->on_collision(other)) break;
			position.x += amount;
			position.z += amount;

			if (!this->on_collision(other)) break;
			position.z -= amount;
			position.z -= amount;

			if (!this->on_collision(other)) break;
			position.z += amount;
			position.y += amount;

			if (!this->on_collision(other)) break;
			position.y -= amount;
			position.y -= amount;

			if (!this->on_collision(other)) break;
			position.y += amount;
			amount += step;
		}
	}

	void BoxCollider::size(const glm::vec3& size)
	{
		this->m_size = size;
		this->m_offset = size / 2.0f;
	}
}