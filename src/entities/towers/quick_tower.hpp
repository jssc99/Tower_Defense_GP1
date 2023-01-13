#pragma once

#include "../tower.hpp"

class Quick : public Tower
{
public:
	inline Quick();
	inline ~Quick() {};

	inline char* getTypeName() const;
};

Quick::Quick()
{
	this->type = Type_Tower::QUICK;
	this->color = DARK_GREEN;
	this->price = 15;
	this->setAttackStats(150.f, 2.f, 1);
}

char* Quick::getTypeName() const
{
	return (char*)"Quick";
}