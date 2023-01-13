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
	this->moveSpeed = 0.7;
	this->loot = 30;
	this->maxHealth = 120;
}

Knight::~Knight()
{
}