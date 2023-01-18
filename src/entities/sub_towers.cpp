#include "sub_towers.hpp"

// BASIC

Basic::Basic()
{
	this->type = Type_Tower::BASIC;
	this->loadTexture("assets/towerDefense_tile181.png");
	this->turret.sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile228.png");
	this->price = 20;
	this->setAttackStats(100.f, 1.f, 5);
}

const char* Basic::getTypeName() const
{
	return "Basic";
}

// QUICK

Quick::Quick()
{
	this->type = Type_Tower::QUICK;
	this->loadTexture("assets/towerDefense_tile183.png");
	this->turret.sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile229.png");
	this->price = 15;
	this->setAttackStats(150.f, 2.f, 1);
}

const char* Quick::getTypeName() const
{
	return "Quick";
}

// SLOW

Slow::Slow()
{
	this->type = Type_Tower::SLOW;
	this->loadTexture("assets/towerDefense_tile182.png");
	this->turret.sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile203.png");
	this->price = 30;
	this->setAttackStats(50.f, 0.f, 0);
}

const char* Slow::getTypeName() const
{
	return "Slow";
}

inline void Slow::attack()
{
	this->current_target->moveSpeed = this->current_target->initMS/2;
}

// EXPLOSIVE

Explosive::Explosive()
{
	this->type = Type_Tower::EXPLOSIVE;
	this->loadTexture("assets/towerDefense_tile180.png");
	this->turret.sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile227.png");
	this->price = 40;
	this->setAttackStats(200.f, 6.f, 15);
}

const char* Explosive::getTypeName() const
{
	return "Explosive";
}