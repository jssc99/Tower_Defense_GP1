#pragma once

#include <imgui.h>

struct float2
{
	float x, y;

	operator ImVec2() { return { x, y }; };
};

constexpr float2 UP = { 0, -1 };
constexpr float2 DOWN = { 0, 1 };
constexpr float2 RIGHT = { 1, 0 };
constexpr float2 LEFT = { -1, 0 };
constexpr float2 STOP = { 0, 0 };