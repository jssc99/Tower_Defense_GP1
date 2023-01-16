#pragma once

class HealthSystem
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