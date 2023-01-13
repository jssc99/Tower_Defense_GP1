#pragma once

#include "../entity.hpp"
#include "healthSystem.hpp"

class Castle : public Entity 
{
public:
	HealthSystem health;

	Castle() {};
	~Castle() {};

	void updateCastle() {};
};