#pragma once

#include "types.hpp"
#include "imgui_utils.hpp"

class Entity
{
public:
	float2 pos;
	ImGuiUtils sprite;

	inline Entity() {}
	inline ~Entity() {}

	virtual void drawEntity() {}
};
