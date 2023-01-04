#pragma once

#include "entity.hpp"
#include "checkpoint.hpp"

static float2 UP;
static float2 DOWN;
static float2 RIGHT;
static float2 LEFT;

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