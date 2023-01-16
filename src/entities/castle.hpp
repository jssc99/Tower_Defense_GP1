#pragma once

#include "../entity.hpp"
#include "health.hpp"

class Castle : public Entity
{
public:
	Health health;

	inline Castle();
	inline ~Castle() {};

	inline void drawHealth();
};

Castle::Castle()
{
	health.maxLife = 250;
	health.life = health.maxLife;
};

void Castle::drawHealth()
{
	ImGui::GetForegroundDrawList()->AddRectFilled({ this->pos.x-(health.life * L_HEALTH_SIZE/2) / health.maxLife, this->pos.y - 50 },
															{ this->pos.x + (health.life*L_HEALTH_SIZE/2)/health.maxLife, this->pos.y - H_HEALTH_SIZE-50 }, BLACK);
};