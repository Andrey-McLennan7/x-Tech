#include <x-Tech/x-Tech.h>

using namespace xTech;

class Asteroid : public Component
{
// Private data members
private:

	float m_movement_speed;
	float m_rotation_speed;

	std::weak_ptr<BoxCollider> m_collider;
	std::weak_ptr<SoundSource> m_explosion;

// Private member functions
private:

	void random_velocity(float& movement, float& rotation);

// Public member functions
public:

	// First to execute when applied
	virtual void on_initialize() override;

	// Executed every iteration
	virtual void on_tick() override;
};