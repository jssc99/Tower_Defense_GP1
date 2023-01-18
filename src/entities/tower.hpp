#pragma once

#include "../entity.hpp"
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
	int price = 0;

	Turret turret;
	Type_Tower type;
	Enemy* current_target = nullptr;

	Tower();
	~Tower();

	void setPos(float2 pos);
	void setPos(float x, float y);

	virtual const char* getTypeName() const;

	void update(Enemy** en, int nbEnemies, int* money);
	void draw(bool drawRadius = true);

	virtual void upgrade(int* money) { /*used by subclasses*/ };

	bool isMouseOverTower() const;

protected:
	void setAttackStats(float attackRadius, float attackSpeed, int attackDmg);
	void upgradeAttackStats(float attackRadius, float attackSpeed, int attackDmg);
	virtual void attack();

private:
	float mAttackRadius = 0.f;
	float mAttackSpeed = 0.f;
	float mAttackCooldown = 0.f;
	int mAttackDmg = 0;

	bool isEnemyInsideRange(Enemy const* en) const;
	void getTarget(Enemy** en, int nbEnemies);
	void attackTarget();
};