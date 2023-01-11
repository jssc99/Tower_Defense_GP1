#pragma once

#include "../entity.hpp"
#include "checkpoint.hpp"
#include "healthSystem.hpp"

class Enemy : public Entity, public HealthSystem
{
public:
	int attackDmg;
	float moveSpeed;
	int loot;
	float2 direction;
	int checkId = 1;

	Enemy() {}
	~Enemy() {}

	void draw() override;
};