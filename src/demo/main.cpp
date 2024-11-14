#include <x-Tech/x-Tech.h>

using namespace xTech;

#undef main
int main()
{
	std::shared_ptr<Core> core{ Core::initialize() };
	std::shared_ptr<Entity> entity{ core->add_entity() };
	std::shared_ptr<TriangleRenderer> triangle{ entity->add_component<TriangleRenderer>() };

	core->run();

	return 0;
}