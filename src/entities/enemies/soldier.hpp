#pragma once

#include "../enemy.hpp"

class Soldier : public Enemy
{
public:
	inline Soldier();
	inline ~Soldier();
};

Soldier::Soldier()
{
	//this->color = RED;
	this->type = Type_Enemy::SOLDIER;
	this->enemy_t.sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile247.png");
	this->attackDmg = 20;
	this->moveSpeed = 1.f;
	this->loot = 10;
	this->health.maxLife = 125;
	this->health.life = this->health.maxLife;
}

Soldier::~Soldier()
{
}