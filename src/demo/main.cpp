#include <x-Tech/x-Tech.h>
#include <rend/rend.h>

using namespace xTech;
using namespace rend;

#undef main
int main()
{
	std::shared_ptr<Core> core{ Core::initialize() };
	std::shared_ptr<Entity> entity{ core->add_entity() };
	std::shared_ptr<TriangleRenderer> triangle{ entity->add_component<TriangleRenderer>() };

	core->run();

	return 0;
}