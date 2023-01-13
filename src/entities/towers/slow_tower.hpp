#pragma once

#include "../tower.hpp"

class Slow : public Tower
{
public:
	inline Slow();
	inline ~Slow() {};

	inline char* getTypeName() const;
	void attack() override;
};

Slow::Slow()
{
	this->type = Type_Tower::SLOW;
	//this->color = CYAN;
	this->sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile182.png");
	this->price = 30;
	this->setAttackStats(50.f, 0.f, 0);
}

char* Slow::getTypeName() const
{
	return (char*)"Slow";
}

inline void Slow::attack()
{
	this->current_target; // TODO slow target down
}