#pragma once

#include "../entity.hpp"
#include "health_system.hpp"

class Castle : public Entity
{
public:
	HealthSystem healthSystem;

	inline Castle();
	~Castle() {};
};

Castle::Castle()
{
	healthSystem.maxHealth = 250;
	healthSystem.health = healthSystem.maxHealth;
};

/*
	void drawHealth()
	{
		ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
		fgDrawlist->AddRectFilled({ this->pos.x, this->pos.y + 50 }, { this->pos.x + 200, this->pos.y + 100 }, GREEN);
	};
	*/