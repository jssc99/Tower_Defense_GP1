#pragma once

#include "castle.hpp"
#include "../grid.hpp"

class Enemy : public Entity
{
public:
	HealthSystem health;
	int attackDmg;
	float moveSpeed;
	int loot;
	float2 direction;
	int checkId;

	Enemy();
	~Enemy() {}

	void setPos(float2 pos);
	void update(Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle);
	void draw() override;

private:
	void move(Checkpoint* listCheckpoint, int nbCheckpoint);
};