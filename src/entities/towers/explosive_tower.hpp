#pragma once

#include "../tower.hpp"

class Explosive : public Tower
{
public:
	float bombRadius;

	inline Explosive();
	inline ~Explosive() {};

	inline char* getType() const;
};

Explosive::Explosive()
{
	this->bombRadius = 10.f;
	this->color = VIOLET;
	this->price = 40;
	this->setAttackStats(200.f, 6.f, 15);
}

char* Explosive::getType() const
{
	return (char*)"Explosive";
}