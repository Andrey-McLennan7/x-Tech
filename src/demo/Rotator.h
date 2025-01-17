#include <x-Tech/x-Tech.h>

using namespace xTech;

class Rotator : public Component
{
	// Private data members
private:



	// Public member functions
public:

	// First to execute when applied
	virtual void on_initialize() override;

	// Executed every iteration
	virtual void on_tick() override;

};