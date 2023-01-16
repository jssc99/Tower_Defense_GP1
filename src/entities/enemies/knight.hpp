#pragma once

#include "../enemy.hpp"

class Knight : public Enemy
{
public:
	inline Knight();
	inline ~Knight();
};

Knight::Knight()
{
	//this->color = BLACK;
	this->type = Type_Enemy::KNIGHT;
	this->enemy_t.sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile246.png");
	this->attackDmg = 50;
	this->moveSpeed = 0.7f;
	this->loot = 30;
	this->health.maxLife = 300;
	this->health.life = this->health.maxLife;
}

Knight::~Knight()
{
}