#pragma once

#include "../grid.hpp"
#include "../health.hpp"

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
	int attackDmg = 0;
	float initMS = 1.f;
	float moveSpeed = 1.f;
	float angle = 0.f;
	int loot = 0;
	float radius = 0.f;
	float actionCD = 0.f;
	float size = 10.f;
	float2 direction = RIGHT;
	int checkId = 1;
	Health health;
	Type_Enemy type = Type_Enemy::NONE;

	Enemy();
	~Enemy();

	void update(const Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle, float gameAcc, Enemy** en);
	void spawn(float2 spawnPoint);
	void draw(bool drawRadius = true);
	bool isDead() const;
	void getDamage(int damage);
	void heal(Enemy** en, float gameAcc);
	bool isMouseOverEnemy() const;

private:
	void move(const Checkpoint* listCheckpoint, int nbCheckpoint, float gameAcc);
};