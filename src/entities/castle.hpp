#pragma once

#include "../entity.hpp"
#include "healthSystem.hpp"

class Castle : public Entity, public HealthSystem
{
public:
	Castle() {};
	~Castle() {};

	void updateCastle() {};
};