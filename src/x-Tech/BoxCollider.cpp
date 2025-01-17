#include "BoxCollider.h"
#include "Transform.h"

#include <iostream>

namespace xTech
{
	void BoxCollider::on_initialize()
	{
		this->m_size = glm::vec3{ 1.0f };
		this->m_offset = glm::vec3{ 0.0f };
	}

	bool BoxCollider::on_collision(const Collider& other) const
	{
		const BoxCollider* _other{ (const BoxCollider*)&other };

		glm::vec3 a{ this->transform()->position() + this->m_offset};
		glm::vec3 b{ _other->transform()->position() + _other->m_offset};

		glm::vec3 ahs{ this->m_size / 2.0f };
		glm::vec3 bhs{ _other->m_size / 2.0f };

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
		float amount{ 0.001f };
		float step{ 0.001f };

		std::shared_ptr<Transform> transform{ this->transform() };

		while (true)
		{
			if (!this->on_collision(other)) break;
			transform->move(glm::vec3{ amount, 0.0f, 0.0f });

			if (!this->on_collision(other)) break;
			transform->move(glm::vec3{ -(amount * 2.0f), 0.0f, 0.0f });

			if (!this->on_collision(other)) break;
			transform->move(glm::vec3{ amount, 0.0f, amount });

			if (!this->on_collision(other)) break;
			transform->move(glm::vec3{ 0.0f, 0.0f, -(amount * 2.0f) });

			if (!this->on_collision(other)) break;
			transform->move(glm::vec3{ 0.0f, amount, amount });

			if (!this->on_collision(other)) break;
			transform->move(glm::vec3{ 0.0f, -(amount * 2.0f), 0.0f});

			if (!this->on_collision(other)) break;
			transform->move(glm::vec3{ 0.0f, amount, 0.0f });

			amount += step;
		}
	}

	void BoxCollider::size(const glm::vec3& size)
	{
		this->m_size = size;
	}

	void BoxCollider::size(float size)
	{
		this->size(glm::vec3{ size });
	}
}