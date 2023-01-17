#pragma once

#include "../entity.hpp"
#include "health_system.hpp"

class Castle : public Entity
{
public:
	HealthSystem healthSystem;

	inline Castle();
	inline ~Castle() {};

	inline void drawHealth();
};

Castle::Castle()
{
	healthSystem.maxHealth = 250;
	healthSystem.health = healthSystem.maxHealth;
};

void Castle::drawHealth()
{
	ImGui::GetForegroundDrawList()->AddRectFilled({ this->pos.x - (healthSystem.health * L_HEALTH_SIZE / 2) / healthSystem.maxHealth, this->pos.y - 50 },
		{ this->pos.x + (healthSystem.health * L_HEALTH_SIZE / 2) / healthSystem.maxHealth, this->pos.y - H_HEALTH_SIZE - 50 }, BLACK);
};