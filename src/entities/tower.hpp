#pragma once

#include "../entity.hpp"
#include "projectile.hpp"
#include "enemy.hpp"

class Tower : public Entity
{
public:
	int price;
	Enemy* current_target;
	//Projectile projectile; //not used for now

	Tower();
	~Tower() { /*if (this->current_target) delete this->current_target;*/ };

	void setPos(float2 pos);
	void setPos(float x, float y);

	virtual char* getType() const;

	void update(Enemy** en, int nbEnemies = 0);
	void draw(bool drawRadius = 1);

	void upgrade();

protected:
	void setAttackStats(float attackRadius, float attackSpeed, int attackDmg);

private:
	float mAttackRadius;
	float mAttackSpeed;
	float mAttackCooldown;
	int mAttackDmg;
	int mUpgradeLvl;

	bool mIsEnemyInsideRange(Enemy* en);
	void mGetTarget(Enemy** en, int nbEnemies);
	void mAttackTarget();
	virtual void mAttack();
};