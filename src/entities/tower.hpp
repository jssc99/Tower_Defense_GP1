#pragma once

#include "../entity.hpp"
#include "projectile.hpp"
#include "enemy.hpp"

class Tower : public Entity
{
public:
	int price;
	Enemy *current_target;
	Projectile projectile;

	Tower();
	~Tower() { delete this->current_target; };

	void setPos(float2 pos);
	void setPos(float x, float y);

	void update(Enemy **en, int nbEnemies = 0);
	void draw() override;

	void upgrade();

private: 
	float mAttackCooldown;
	float mActionRadius;
	float mAttackSpeed;
	int mAttackDmg;
	int mUpgradeLvl;

	bool mIsEnemyInsideRange(Enemy* en);
	void mGetTarget(Enemy** en, int nbEnemies);
	void mAttackTarget();
};