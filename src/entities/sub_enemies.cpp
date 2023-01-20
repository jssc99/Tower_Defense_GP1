#include "sub_enemies.hpp"

// HEALER

Healer::Healer()
{
	this->mType = Type_Enemy::HEALER;
	this->loadTexture("assets/towerDefense_tile245.png");
	this->mAttackDmg = 5;
	this->mInitMS = 90.f;
	this->mMoveSpeed = mInitMS;
	this->mLoot = 10;
	this->mHealth.maxLife = 40;
	this->mHealth.life = this->mHealth.maxLife;
	this->mRadius = 100.f;
}

// KNIGHT

Knight::Knight()
{
	this->mType = Type_Enemy::KNIGHT;
	this->loadTexture("assets/towerDefense_tile246.png");
	this->mAttackDmg = 50;
	this->mInitMS = 42.f;
	this->mMoveSpeed = mInitMS;
	this->mLoot = 20;
	this->mHealth.maxLife = 100;
	this->mHealth.life = this->mHealth.maxLife;
	this->mRadius = 5.f;
}

// SOLDIER

Soldier::Soldier()
{
	this->mType = Type_Enemy::SOLDIER;
	this->loadTexture("assets/towerDefense_tile247.png");
	this->mAttackDmg = 20;
	this->mInitMS = 60.f;
	this->mMoveSpeed = mInitMS;
	this->mLoot = 5;
	this->mHealth.maxLife = 60;
	this->mHealth.life = this->mHealth.maxLife;
	this->mRadius = 5.f;
}