#pragma once

#include "types.hpp"
#include "imgui_utils.hpp"

class Entity
{
public:
	float2 pos;
	ImGuiUtils sprite;

	Entity() virtual {};
	~Entity() virtual {};

	virtual void drawEntity() {};
};
