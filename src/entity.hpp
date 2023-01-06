#pragma once

#include "types.hpp"
#include "imgui_utils.hpp"

#define BLACK ImColor(0.f, 0.f, 0.f, 1.f)
#define RED ImColor(1.f, 0.f, 0.f, 1.f);
#define GREEN ImColor(0.f, 1.f, 0.f, 1.f)
#define ORANGE ImColor(1.f, 0.5f, 0.f, 1.f)
#define VIOLET ImColor(0.5f, 0.f, 1.f, 1.f)
#define BLUE ImColor(0.f, 0.f, 1.f, 1.f)

class Entity
{
public:
	float2 pos;
	ImGuiUtils sprite;

	inline Entity() {}
	inline ~Entity() {}

	virtual void drawEntity() {}
};
