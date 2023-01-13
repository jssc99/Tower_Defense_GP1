#pragma once

#include "../enemy.hpp"

class Healer : public Enemy
{
public:
	inline Healer();
	inline ~Healer();
};

Healer::Healer()
{
	this->color = CYAN;
	this->attackDmg = 5;
	this->moveSpeed = 1.5f;
	this->loot = 5;
	this->health.maxHealth = 30;
}

Healer::~Healer()
{
}