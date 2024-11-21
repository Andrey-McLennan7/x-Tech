#include <x-Tech/x-Tech.h>

using namespace xTech;

class EntityMover : public Component
{
private:

	vec3* position;
	float speed;

public:

	virtual void on_initialize() override
	{
		position = &this->transform()->m_position;

		position->x = -10.0f;
		speed = 10.0f;
	}

	virtual void on_tick() override
	{
		position->x += speed * this->window()->delta_time();
	}
};

#undef main
int main()
{
	// Create core and add resources
	std::shared_ptr<Core> core{ Core::initialize() };
	std::shared_ptr<Shader> triangle_shader{ core->cache()->load<Shader>("Shader/basic") };
	std::shared_ptr<Audio> triangle_audio{ core->cache()->load<Audio>("Audio/dixie_horn")};

	// Create entity and attach components
	std::shared_ptr<Entity> triangle_entity{ core->add_entity() };
	std::shared_ptr<TriangleRenderer> triangle{ triangle_entity->add_component<TriangleRenderer>() };
	std::shared_ptr<SoundSource> triangle_sound_source{ triangle_entity->add_component<SoundSource>() };

	triangle_entity->add_component<EntityMover>();
	triangle_sound_source->audio(triangle_audio);
	triangle_sound_source->play();

	core->run();

	return 0;
}