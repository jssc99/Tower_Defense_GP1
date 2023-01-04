#pragma once

#include "types.hpp"

struct Direction
{
	static float2 UP;
	static float2 DOWN;
	static float2 RIGHT;
	static float2 LEFT;
};

class Checkpoint
{
public:
	int value;
	float2 newDirection;

	Checkpoint(int val, float2 dir) : value(val), newDirection(dir) {};
	~Checkpoint() {};
};
