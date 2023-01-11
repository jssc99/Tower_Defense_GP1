#pragma once

#include "../entity.hpp"
#include "healthSystem.hpp"

class Castle : public Entity, public HealthSystem
{
public:
	Castle() {};
	~Castle() {};

	void drawHealth()
	{
		ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
		fgDrawlist->AddRectFilled({ this->pos.x, this->pos.y + 50 }, { this->pos.x + 200, this->pos.y + 100 }, GREEN);
	};
};