#pragma once

#include "../tower.hpp"

class Explosive : public Tower
{
public:
	float bombRadius;

	inline Explosive();
	inline ~Explosive() {};

	inline char* getTypeName() const;
};

Explosive::Explosive()
{
	this->type = Type_Tower::EXPLOSIVE;
	this->bombRadius = 10.f;
	//this->color = VIOLET;
	this->sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile180.png");
	this->turret = ImGuiUtils::LoadTexture("assets/towerDefense_tile227.png");
	this->price = 40;
	this->setAttackStats(200.f, 6.f, 15);
}

char* Explosive::getTypeName() const
{
	return (char*)"Explosive";
}