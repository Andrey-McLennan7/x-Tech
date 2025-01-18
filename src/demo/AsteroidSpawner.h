#include <x-Tech/x-Tech.h>

#include <vector>
#include <memory>

using namespace xTech;

class Player;

class AsteroidSpawner : public Component
{
// Private data members
private:

	float m_timer;

// Public member functions
public:

	// First to execute when applied
	virtual void on_initialize() override;

	// Executed every iteration
	virtual void on_tick() override;
};