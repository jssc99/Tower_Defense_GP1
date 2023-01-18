#include "sub_enemies.hpp"

Healer::Healer()
{
	this->type = Type_Enemy::HEALER;
	this->loadTexture("assets/towerDefense_tile245.png");
	this->attackDmg = 5;
	this->initMS = 90.f;
	this->moveSpeed = initMS;
	this->loot = 5;
	this->health.maxLife = 50;
	this->health.life = this->health.maxLife;
	this->radius = 100.f;
}



Knight::Knight()
{
	this->type = Type_Enemy::KNIGHT;
	this->loadTexture("assets/towerDefense_tile246.png");
	this->attackDmg = 50;
	this->initMS = 42.f;
	this->moveSpeed = initMS;
	this->loot = 30;
	this->health.maxLife = 300;
	this->health.life = this->health.maxLife;
}



Soldier::Soldier()
{
	this->type = Type_Enemy::SOLDIER;
	this->loadTexture("assets/towerDefense_tile247.png");
	this->attackDmg = 20;
	this->initMS = 60.f;
	this->moveSpeed = initMS;
	this->loot = 10;
	this->health.maxLife = 125;
	this->health.life = this->health.maxLife;
}
