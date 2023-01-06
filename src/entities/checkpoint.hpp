#pragma once

#include "../types.hpp"
#include "../entity.hpp"

class Checkpoint : public Entity
{
public:
	int id;
	float2 newDirection;

	Checkpoint() : id(0), newDirection( {0,0} ) {};
	Checkpoint(int id, float2 pos, float2 dir) : id(id), newDirection(dir) { this->pos = pos; };
	~Checkpoint() {};

	void draw() override
	{
		ImGui::GetForegroundDrawList()->AddCircleFilled({ this->pos.x, this->pos.y }, 3.f, BLUE);
	};
};
