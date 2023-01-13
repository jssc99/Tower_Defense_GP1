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

	void update(Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle);
	void spawn(Grid* grid);
	void draw() override;

private:
	void mMove(Checkpoint* listCheckpoint, int nbCheckpoint);
};