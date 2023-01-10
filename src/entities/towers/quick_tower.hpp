#pragma once

#include "../tower.hpp"

class Quick : public Tower
{
public:
	inline Quick();
	inline ~Quick();
};

Quick::Quick()
{
	this->color = GREEN;
	this->price = 15;
	this->actionRadius = 150.f;
	this->attackDmg = 1;
	this->attackSpeed = 2.f;
}

Quick::~Quick()
{
}
