#include "sub_enemies.hpp"

Healer::Healer()
{
	//this->color = CYAN;
	this->type = Type_Enemy::HEALER;
	this->sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile245.png");
	this->attackDmg = 5;
	this->initMS = 1.5f;
	this->moveSpeed = initMS;
	this->loot = 5;
	this->health.maxLife = 50;
	this->health.life = this->health.maxLife;
}

Healer::~Healer()
{
}

Knight::Knight()
{
	//this->color = BLACK;
	this->type = Type_Enemy::KNIGHT;
	this->sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile246.png");
	this->attackDmg = 50;
	this->initMS = 0.7f;
	this->moveSpeed = initMS;
	this->loot = 30;
	this->health.maxLife = 300;
	this->health.life = this->health.maxLife;
}

Knight::~Knight()
{
}

Soldier::Soldier()
{
	//this->color = RED;
	this->type = Type_Enemy::SOLDIER;
	this->sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile247.png");
	this->attackDmg = 20;
	this->initMS = 1.f;
	this->moveSpeed = initMS;
	this->loot = 10;
	this->health.maxLife = 125;
	this->health.life = this->health.maxLife;
}

Soldier::~Soldier()
{
}