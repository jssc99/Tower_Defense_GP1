#pragma once

#include "../entity.hpp"
#include "health.hpp"

class Castle : public Entity
{
public:
	Health health;

	inline Castle();
	inline ~Castle() {};
};

inline Castle::Castle()
{
	health.maxLife = 250;
	health.life = health.maxLife;
	health.posCenter.x = SQUARE_SIZE * 25 + SQUARE_SIZE/2;
	health.posCenter.y = SQUARE_SIZE*22;
};