#include <x-Tech/x-Tech.h>

using namespace xTech;

class Shoot;
class Controls;
class Asteroid;
class AsteroidSpawner;
class CollisionResponce;

class Player : public Component
{
// Private data members
private:

	float m_health;
	float m_distance;

	std::weak_ptr<BoxCollider> m_collider;

	std::vector<std::weak_ptr<Entity>> m_scene_asteroids;

// Public member functions
public:

	// First to execute when applied
	virtual void on_initialize() override;

	// Executed every iteration
	virtual void on_tick() override;

	friend class AsteroidSpawner;
};