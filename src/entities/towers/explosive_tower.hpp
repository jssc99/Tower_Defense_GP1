#pragma once

#include "../tower.hpp"

class Explosive : public Tower
{
public:
	float bombRadius;

	inline Explosive();
	inline ~Explosive();
};

Explosive::Explosive()
{
	this->bombRadius = 10.f;
	this->color = VIOLET;
	this->price = 40;
	this->actionRadius = 200.f;
	this->attackDmg = 15;
	this->attackSpeed = 6.f;
}

Explosive::~Explosive()
{
}
