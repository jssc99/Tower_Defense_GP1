#pragma once

#include "../entity.hpp"
#include "health.hpp"

#define CASTLE_LIFE_POS { H_WIDTH + 180, HEIGHT /*- 30 + 30*/ } // (+30, off center health bar)

class Castle : public Entity
{
public:
	Health health;

	inline Castle() {
		health.posCenter = CASTLE_LIFE_POS;
		health.maxLife = 250;
		health.life = health.maxLife;
	};
	inline ~Castle() {};

	inline bool isDead() const { return this->health.life <= 0; };
};