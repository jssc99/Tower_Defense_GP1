#pragma once

#include "../entity.hpp"
#include "../health.hpp"

#define CASTLE_LIFE_POS { H_WIDTH + 180, HEIGHT /*- 30 + 30*/ } // (+30, off center health bar)

class Castle : public Entity
{
public:
	Health health;

	inline Castle() {
		this->health.posCenter = CASTLE_LIFE_POS;
		this->health.maxLife = 100;
		this->health.life = health.maxLife;
	};
	inline ~Castle() {};

	inline bool isDead() const { return this->health.life <= 0; };
};