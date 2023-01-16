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

struct Enemy_t
{
	float angle;
	Texture sprite;
};

class Enemy : public Entity
{
public:
	int attackDmg;
	float moveSpeed;
	int loot;
	float2 direction;
	int checkId;
	Health health;
	Type_Enemy type;
	Enemy_t enemy_t;

	Enemy();
	~Enemy() {}

	void update(Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle);
	void spawn(Grid* grid);
	void draw() override;
	void drawHealth();
	bool isDead();

private:
	void move(Checkpoint* listCheckpoint, int nbCheckpoint);
	void die();
};