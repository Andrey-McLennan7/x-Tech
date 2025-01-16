#include "Data.h"

#include <iostream>

void Data::on_initialize()
{
	this->m_health = 100.0f;
	this->m_points = 0.0f;
	this->m_distance = 0.0f;
}

void Data::on_tick()
{
	this->m_distance += 2.5f * this->delta_time();

	// Check health condition
	if (this->m_health <= 0.00000001f)
	{
		system("cls");
		std::cout << "GAME OVER\n" << std::endl;
		system("pause");

		this->core()->end();
	}
}