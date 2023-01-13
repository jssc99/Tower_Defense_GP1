#pragma once

#include "../tower.hpp"

class Basic : public Tower
{
public:
	inline Basic();
	inline ~Basic() {};

	inline char* getTypeName() const;
};

Basic::Basic()
{
	this->type = Type_Tower::BASIC;
	this->color = BLUE;
	this->price = 20;
	this->setAttackStats(100.f, 4.f, 5);
}

char* Basic::getTypeName() const
{
	return (char*)"Basic";
}