#pragma once

#include "../enemy.hpp"

class Healer : public Enemy
{
public:
	inline Healer();
	inline ~Healer();
};

Healer::Healer()
{
	//this->color = CYAN;
	this->type = Type_Enemy::HEALER;
	this->enemy_t.sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile245.png");
	this->attackDmg = 5;
	this->moveSpeed = 5;
	this->loot = 5 ;
	this->health.maxLife = 50;
	this->health.life = this->health.maxLife;
}

Healer::~Healer()
{
}