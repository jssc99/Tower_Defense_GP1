#pragma once

#include "../entity.hpp"
#include "castle.hpp"
#include "../grid.hpp"
#include "health.hpp"

enum class Type_Enemy : char
{
	NONE = 'n',
	SOLDIER = 's',
	KNIGHT = 'k',
	HEALER = 'h'
};

class Enemy : public Entity
{
public:
	int attackDmg;
	float initMS;
	float moveSpeed;
	float angle;
	int loot;
	float2 direction;
	int checkId;
	Health health;
	Type_Enemy type;

	Enemy();
	~Enemy();

	void update(Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle);
	void spawn(Grid* grid);
	void draw() override;
	bool isDead();
	void getDamage(int damage);

private:
	void move(Checkpoint* listCheckpoint, int nbCheckpoint);
};