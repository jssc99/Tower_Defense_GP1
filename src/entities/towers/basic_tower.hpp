#pragma once

#include "../tower.hpp"

class Basic : public Tower
{
public:
	inline Basic();
	inline ~Basic();
};

Basic::Basic()
{
	this->color = BLUE;
	this->price = 20;
	this->actionRadius = 100.f;
	this->attackDmg = 5;
	this->attackSpeed = 4.f;
}

Basic::~Basic()
{
}
