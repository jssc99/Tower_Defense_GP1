#pragma once

#include "../entity.hpp"

class HealthSystem : public Entity
{
public:
	int maxHealth;
	int health;

	HealthSystem() { maxHealth = 0; health = 0; };
	~HealthSystem() {};
};