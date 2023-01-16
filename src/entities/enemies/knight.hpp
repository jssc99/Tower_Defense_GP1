#pragma once

#include "../enemy.hpp"

class Knight : public Enemy
{
public:
	inline Knight();
	inline ~Knight();
};

Knight::Knight()
{
	this->color = BLACK;
	this->attackDmg = 50;
	this->moveSpeed = 0.7f;
	this->loot = 30;
	this->healthSystem.maxHealth = 300;
	this->healthSystem.health = this->healthSystem.maxHealth;
}

Knight::~Knight()
{
}