#pragma once

#include "types.hpp"

constexpr float2 UP = { 0, -1 };
constexpr float2 DOWN = { 0, 1 };
constexpr float2 RIGHT = { 1, 0 };
constexpr float2 LEFT = { -1, 0 };

class Checkpoint
{
public:
	int value;
	float2 newDirection;

	Checkpoint() : value(0), newDirection( {0,0} ) {};
	Checkpoint(int val, float2 dir) : value(val), newDirection(dir) {};
	~Checkpoint() {};
};
