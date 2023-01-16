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
	this->moveSpeed = 5;
	this->loot = 5 ;
	this->healthSystem.maxHealth = 50;
	this->healthSystem.health = this->healthSystem.maxHealth;
}

Healer::~Healer()
{
}