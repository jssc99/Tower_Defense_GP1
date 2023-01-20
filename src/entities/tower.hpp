#pragma once

#include "projectile.hpp"
#include "enemy.hpp"

constexpr auto UPGRADE_COST = 15;

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
	Projectile projectile;
};

class Tower : public Entity
{
public:
	Tower();
	~Tower();

	void setPos(float2 pos);
	void setPos(float x, float y);

	virtual const char* getTypeName() const;
	Type_Tower getType() const;
	int getPrice() const;

	void update(Enemy** en, int nbEnemies, int* money, float gameSpeed);
	void draw(bool drawRadius = true);
	void drawTarget();

	bool isMouseOverTower() const;
	bool hasTarget() const;

protected:	
	Turret mTurret;
	Type_Tower mType;
	Enemy* mCurrentTarget = nullptr;

	int mUpgradeLvl = 0;
	int mPrice = 0;

	virtual void attack();
	void setAttackStats(float attackRadius, float attackSpeed, int attackDmg);
	void upgradeAttackStats(float attackRadius, float attackSpeed, int attackDmg);

	virtual void upgrade(int* money) { /*used by subclasses*/ };

private:
	int mAttackDmg = 0;
	float mAttackSpeed = 0.f;
	float mAttackRadius = 0.f;
	float mAttackCooldown = 0.f;

	bool isEnemyInsideRange(Enemy* en) const;
	void getTarget(Enemy** en, int nbEnemies);
	void attackTarget(float gameSpeed);
};