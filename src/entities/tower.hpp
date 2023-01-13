#pragma once

#include "../entity.hpp"
#include "projectile.hpp"
#include "enemy.hpp"

enum class Type_Tower : char
{
	NONE = 'n',
	BASIC = 'b',
	QUICK = 'q',
	EXPLOSIVE = 'e',
	SLOW = 's'
};

class Tower : public Entity
{
public:
	int price;
	Type_Tower type;
	Enemy* current_target;
	//Projectile projectile; //not used for now

	Tower();
	~Tower() { /*if (this->current_target) delete this->current_target;*/ };

	void setPos(float2 pos);
	void setPos(float x, float y);

	virtual char* getTypeName() const;

	void update(Enemy** en, int nbEnemies = 0);
	void draw(bool drawRadius = 1);

	void upgrade();

	bool isMouseOverTower();

protected:
	void setAttackStats(float attackRadius, float attackSpeed, int attackDmg);
	virtual void attack();

private:
	float mAttackRadius;
	float mAttackSpeed;
	float mAttackCooldown;
	int mAttackDmg;
	int mUpgradeLvl;

	bool isEnemyInsideRange(Enemy* en);
	void getTarget(Enemy** en, int nbEnemies);
	void attackTarget();
};