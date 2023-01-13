#pragma once

#include "../enemy.hpp"

class Soldier : public Enemy
{
public:
	inline Soldier();
	inline ~Soldier();
};

Soldier::Soldier()
{
	this->color = RED;
	this->attackDmg = 20;
	this->moveSpeed = 1.f;
	this->loot = 10;
	this->health.maxHealth = 50;
}

Soldier::~Soldier()
{
}