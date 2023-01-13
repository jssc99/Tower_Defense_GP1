#pragma once

#include "../game.hpp"
class Castle;
class Grid;

class Enemy : public Entity, public HealthSystem
{
public:
	int attackDmg;
	float moveSpeed;
	int loot;
	float2 direction;
	int checkId;

	Enemy();
	~Enemy() {}

	void setPos(float2 pos);
	void update(Grid* grid, Castle* castle, int nbEnemies);
	void draw() override;
private:
	void mMove(Grid* grid, Castle* castle, int nbEnemies);
};