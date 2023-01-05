#pragma once

#include "../entity.hpp"

class Tower : public Entity
{
public:
	int price;
	float actionRadius;
	float attackSpeed;
	int attackDmg;
	int upgradeLvl;
	float2 target;
	// add Projectile

	Tower() virtual {};
	~Tower() virtual {};

	void updateTower() virtual {};
};