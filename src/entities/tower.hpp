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

struct Turret
{
	float angle = 0.f;
	Texture sprite;
};

class Tower : public Entity
{
public:
	int price = 0;
	Turret turret;
	Type_Tower type;
	Enemy* current_target = nullptr;
	//Projectile projectile; //not used for now

	Tower();
	~Tower();

	void setPos(float2 pos);
	void setPos(float x, float y);

	virtual const char* getTypeName() const;

	void update(Enemy** en, float gameAcc, int nbEnemies = 0);
	void draw(bool drawRadius = true);

	void upgrade();

	bool isMouseOverTower() const;

protected:
	void setAttackStats(float attackRadius, float attackSpeed, int attackDmg);
	virtual void attack();

private:
	float mAttackRadius = 0.f;
	float mAttackSpeed = 0.f;
	float mAttackCooldown = 0.f;
	int mAttackDmg = 0;
	int mUpgradeLvl = 0;

	bool isEnemyInsideRange(Enemy const* en) const;
	void getTarget(Enemy** en, int nbEnemies);
	void attackTarget(float gameAcc);
};