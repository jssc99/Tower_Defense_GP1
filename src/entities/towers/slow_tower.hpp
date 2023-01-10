#pragma once

#include "../tower.hpp"

class Slow : public Tower
{
public:
	inline Slow();
	inline ~Slow();
};

Slow::Slow()
{
	this->color = CYAN;
	this->price = 30;
	this->actionRadius = 50.f;
	this->attackDmg = 0;
	this->attackSpeed = 2.f;
}

Slow::~Slow()
{
}
