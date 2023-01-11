#pragma once

#include "../tower.hpp"

class Quick : public Tower
{
public:
	inline Quick();
	inline ~Quick() {};

	inline char* getType() const;
};

Quick::Quick()
{
	this->color = GREEN;
	this->price = 15;
	this->setAttackStats(150.f, 2.f, 1);
}

char* Quick::getType() const
{
	return (char*)"Quick";
}