#include "sub_towers.hpp"

// BASIC

Basic::Basic()
{
	this->mType = Type_Tower::BASIC;
	this->loadTexture("assets/towerDefense_tile181.png");
	this->mTurret.sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile228.png");
	this->mTurret.projectile.loadTexture("assets/towerDefense_tile273.png");
	this->mPrice = 20;
	this->setAttackStats(100.f, 2.f, 10);
}

const char* Basic::getTypeName() const
{
	return "Basic";
}

void Basic::upgrade(int* money)
{
	if (this->mUpgradeLvl < 5 && *money - UPGRADE_COST >= 0) { this->upgradeAttackStats(5.f, -0.1f, 1); *money -= UPGRADE_COST; }
}

// QUICK

Quick::Quick()
{
	this->mType = Type_Tower::QUICK;
	this->loadTexture("assets/towerDefense_tile183.png");
	this->mTurret.sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile229.png");
	this->mTurret.projectile.loadTexture("assets/towerDefense_tile272.png");
	this->mPrice = 15;
	this->setAttackStats(150.f, 0.5f, 1);
}

const char* Quick::getTypeName() const
{
	return "Quick";
}

void Quick::upgrade(int* money)
{
	if (this->mUpgradeLvl < 5 && *money - UPGRADE_COST >= 0) { this->upgradeAttackStats(1.f, -0.02f, 2); *money -= UPGRADE_COST; }
}

// SLOW

Slow::Slow()
{
	this->mType = Type_Tower::SLOW;
	this->loadTexture("assets/towerDefense_tile182.png");
	this->mTurret.sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile203.png");
	this->mPrice = 30;
	this->setAttackStats(50.f, 0.f, 0);
}

const char* Slow::getTypeName() const
{
	return "Slow";
}

void Slow::upgrade(int* money)
{
	if (this->mUpgradeLvl < 5 && *money - UPGRADE_COST >= 0) { this->upgradeAttackStats(8.f, 0.f, 0); *money -= UPGRADE_COST; }
}

void Slow::attack()
{
	this->mCurrentTarget->setMoveSpeed(0.5);
}

// EXPLOSIVE

Explosive::Explosive()
{
	this->mType = Type_Tower::EXPLOSIVE;
	this->loadTexture("assets/towerDefense_tile180.png");
	this->mTurret.sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile227.png");
	this->mTurret.projectile.loadTexture("assets/towerDefense_tile274.png");
	this->mPrice = 40;
	this->setAttackStats(130.f, 4.f, 30);
}

const char* Explosive::getTypeName() const
{
	return "Explosive";
}

void Explosive::upgrade(int* money)
{
	if (this->mUpgradeLvl < 5 && *money - UPGRADE_COST >= 0) { this->upgradeAttackStats(5.f, -0.2f, 3); *money -= UPGRADE_COST; }
}