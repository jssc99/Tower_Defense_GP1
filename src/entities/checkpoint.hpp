#pragma once

#include "../types.hpp"

class Checkpoint : public Entity
{
public:
	int value;
	float2 newDirection;

	Checkpoint() : value(0), newDirection( {0,0} ) {};
	Checkpoint(int val, float2 dir) : value(val), newDirection(dir) {};
	~Checkpoint() {};

	void drawEntity() override
	{
		ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
		fgDrawlist->AddCircleFilled({ pos.x, pos.y }, 3, ImColor(0.f, 0.f, 1.f));
	};
};
