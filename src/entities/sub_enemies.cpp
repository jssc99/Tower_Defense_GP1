#include "sub_enemies.hpp"

Healer::Healer()
{
	this->type = Type_Enemy::HEALER;
	this->loadTexture("assets/towerDefense_tile245.png");
	this->attackDmg = 5;
	this->initMS = 1.2f;
	this->moveSpeed = initMS;
	this->loot = 10;
	this->health.maxLife = 40;
	this->health.life = this->health.maxLife;
}

Knight::Knight()
{
	this->type = Type_Enemy::KNIGHT;
	this->loadTexture("assets/towerDefense_tile246.png");
	this->attackDmg = 50;
	this->initMS = 0.7f;
	this->moveSpeed = initMS;
	this->loot = 20;
	this->health.maxLife = 100;
	this->health.life = this->health.maxLife;
}

Soldier::Soldier()
{
	this->type = Type_Enemy::SOLDIER;
	this->loadTexture("assets/towerDefense_tile247.png");
	this->attackDmg = 20;
	this->initMS = 1.f;
	this->moveSpeed = initMS;
	this->loot = 5;
	this->health.maxLife = 30;
	this->health.life = this->health.maxLife;
}