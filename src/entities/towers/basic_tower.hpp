#pragma once

#include "../tower.hpp"

class Basic : public Tower
{
public:
	inline Basic();
	inline ~Basic() {};

	inline char* getType() const;
};

Basic::Basic()
{
	this->color = BLUE;
	this->price = 20;
	this->setAttackStats(100.f, 4.f, 5);
}

char* Basic::getType() const
{
	return (char*)"Basic";
}