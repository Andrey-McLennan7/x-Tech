#include "RigidBody.h"
#include "Core.h"
#include "Collider.h"
#include "Entity.h"
#include "Transform.h"

#include <vector>
#include <memory>

namespace xTech
{
	void RigidBody::on_tick()
	{
		std::vector<std::shared_ptr<Collider>> colliders;

		this->core()->find<Collider>(colliders);

		std::vector<std::shared_ptr<Collider>>::iterator itr1;
		for (itr1 = colliders.begin(); itr1 != colliders.end(); ++itr1)
		{
			std::vector<std::shared_ptr<Collider>>::iterator itr2;
			for (itr2 = colliders.begin(); itr2 != colliders.end(); ++itr2)
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