#include <x-Tech/x-Tech.h>

using namespace xTech;

class Player : public Component
{
private:

	vec3 abc;

public:

	virtual void on_initialize() override
	{
		Debug::print("Player::initialize()\n");
	}

	virtual void on_tick() override
	{
		Debug::print("Player::tick()\n");
	}

	virtual void on_display() override
	{
		Debug::print("Player::display()\n");
	}

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