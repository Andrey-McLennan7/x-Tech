#include "RigidBody.h"
#include "Core.h"
#include "Collider.h"
#include "Entity.h"

namespace xTech
{
	void RigidBody::on_tick()
	{
		this->core()->find<Collider>(this->m_colliders);

		std::vector<std::shared_ptr<Collider>>::iterator itr1;
		for (itr1 = this->m_colliders.begin(); itr1 != this->m_colliders.end(); ++itr1)
		{
			std::vector<std::shared_ptr<Collider>>::iterator itr2;
			for (itr2 = this->m_colliders.begin(); itr2 != this->m_colliders.end(); ++itr2)
			{
				if (itr1 == itr2)
				{
					continue;
				}

				std::shared_ptr<Collider> ec2{ (*itr2)->entity()->get_component<Collider>() };

				if ((*itr1)->on_collision(*ec2))
				{
					(*itr1)->get_collision_response(*ec2);
				}
			}
		}
	}
}