#pragma once

#include "../entity.hpp"
#include "../checkpoint.hpp"

class Enemy : public Entity
{
public:
	int attackDmg;
	float moveSpeed;
	int loot;
	float2 direction;

	Enemy() {}
	~Enemy() {}

	void drawEntity() override;
};