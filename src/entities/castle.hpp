#pragma once

#include "../entity.hpp"
#include "health.hpp"

class Castle : public Entity
{
public:
	Health health;

	inline Castle() {
		health.maxLife = 250;
		health.life = health.maxLife;
	};
	inline ~Castle() {};

	inline bool isDead() { return this->health.life <= 0; };
};