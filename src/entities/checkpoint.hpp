#pragma once

#include "../entity.hpp"

class Checkpoint : public Entity
{
public:
	int id;
	float2 newDirection;

	inline Checkpoint() : id(0), newDirection({ 0,0 }) {};
	inline Checkpoint(int id, float2 pos, float2 dir) : id(id), newDirection(dir) { this->pos = pos; };
	inline ~Checkpoint() {};

	inline void draw() override
	{
		ImGui::GetBackgroundDrawList()->AddCircleFilled(this->pos, 3.f, BLUE);
	};
};