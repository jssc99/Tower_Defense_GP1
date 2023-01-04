#pragma once

class HealthSystem
{
public:
	int maxHealth;
	int health;

	HealthSystem() {};
	~HealthSystem() {};

	virtual void drawLifeBar() {};
};

void HealthSystem::drawLifeBar virtual()
{
	// TODO
};