#pragma once

#include "../entity.hpp"

class HealthSystem : public Entity
{
public:
	int maxHealth;
	int health;

	inline HealthSystem();
	~HealthSystem() {};
};

HealthSystem::HealthSystem()
{
	maxHealth = 0;
	health = 0;
};