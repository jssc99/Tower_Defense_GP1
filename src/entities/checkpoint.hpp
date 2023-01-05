#pragma once

#include "../types.hpp"

class Checkpoint : public Entity
{
public:
	int value;
	float2 newDirection;

	Checkpoint() : value(0), newDirection( {0,0} ) {};
	Checkpoint(int val, float2 dir) : value(val), newDirection(dir) {};
	~Checkpoint() {};
};
