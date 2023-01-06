#pragma once

#include "../types.hpp"
#include "../entity.hpp"

class Checkpoint : public Entity
{
public:
	int id;
	float2 newDirection;

	Checkpoint() : id(0), newDirection( {0,0} ) {};
	Checkpoint(int id, float2 dir) : id(id), newDirection(dir) {};
	~Checkpoint() {};

	void drawEntity() override
	{
		ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
		fgDrawlist->AddCircleFilled({ pos.x, pos.y }, 3, ImColor(0.f, 0.f, 1.f));
	};
};
