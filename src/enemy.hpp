#prama once

#include "entity.hpp"

class Enemy : public Entity
{
public:
	int attackDmg;
	float moveSpeed;
	int loot;

	Enemy() virtual {};
	~Enemy() virtual {};

	void updateEnemy() virtual {};
};