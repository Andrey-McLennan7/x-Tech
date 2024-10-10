#include <x-Tech/x-Tech.h>

using namespace xTech;

class Player : public Component
{
private:



public:



};

#undef main
int main()
{
	std::shared_ptr<Core> core{ Core::initialize() };

	std::shared_ptr<Entity> entity{ core->add_entity() };
	std::shared_ptr<Player> player{ entity->add_component<Player>() };

	core->run();

	return 0;
}