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
	this->moveSpeed = 1;
	this->loot = 10;
}

Soldier::~Soldier()
{
}