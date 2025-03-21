#include <x-Tech/x-Tech.h>

#include <vector>

using namespace xTech;

class Movement;
class Shoot;

class Controls : public Component
{
// Private data members
private:

	float m_speed;

	std::weak_ptr<SoundSource> m_sound;
	std::weak_ptr<Shoot> m_shoot;

// Public member functions
public:

	// First to execute when applied
	virtual void on_initialize() override;

	// Executed every iteration
	virtual void on_tick() override;

	friend class Movement;
};