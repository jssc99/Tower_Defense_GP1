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
	Enemy();
	~Enemy();

	void update(const Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle, float gameSpeed, Enemy** en);
	void draw(bool drawRadius = true);

	void getDamage(int damage);
	void spawn(float2 spawnPoint);
	void heal(Enemy** en, float gameSpeed);

	void setMoveSpeed(float s);
	float getSize();
	int getLoot();

	bool isDead() const;
	bool isMouseOverEnemy() const;
	bool isAtEndOfPath(int nbCheckpoints);

protected:
	Type_Enemy mType = Type_Enemy::NONE;
	int mAttackDmg = 0;
	int mCheckId = 1;
	int mLoot = 0;
	float mMoveSpeed = 1.f;
	float mInitMS = 1.f;
	float mRadius = 0.f;
	float mSize = 10.f;
	Health mHealth;

private:
	float2 mDirection = RIGHT;
	float mActionCD = 0.f;
	float mAngle = 0.f;

	void move(const Checkpoint* listCheckpoint, int nbCheckpoint, float gameSpeed);
};