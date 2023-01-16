#pragma once

#include "castle.hpp"
#include "../grid.hpp"
#include "health_system.hpp"

class Enemy : public Entity
{
public:
	int attackDmg;
	float moveSpeed;
	int loot;
	float2 direction;
	int checkId;
	HealthSystem healthSystem;
	//inital ms: TODO

	Enemy();
	~Enemy() {}

	void update(Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle);
	void spawn(Grid* grid);
	void draw() override;
	void drawHealth();

private:
	void move(Checkpoint* listCheckpoint, int nbCheckpoint);
	void die();
};