#include <x-Tech/x-Tech.h>

#include <iostream>

int safe_main();

int main()
{
	try
	{
		safe_main();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

int safe_main()
{
	// Create core
	std::shared_ptr<xTech::Core> core{ xTech::Core::initialize() };

	// Prevent the window from being resized
	core->window()->resizable(false);

	// Run engine
	core->run();

	return 0;
}