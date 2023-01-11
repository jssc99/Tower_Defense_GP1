#pragma once

#include "types.hpp"
#include "imgui_utils.hpp"

#define WHITE ImColor(1.f, 1.f, 1.f, 1.f)
#define BLACK ImColor(0.f, 0.f, 0.f, 1.f)
#define RED ImColor(1.f, 0.f, 0.f, 1.f)
#define GREEN ImColor(0.f, 1.f, 0.f, 1.f)
#define ORANGE ImColor(1.f, 0.5f, 0.f, 1.f)
#define VIOLET ImColor(0.5f, 0.f, 1.f, 1.f)
#define BLUE ImColor(0.f, 0.f, 1.f, 1.f)

class Entity
{
public:
	float2 pos;
	ImGuiCol color; // while there's no texture
	//ImGuiUtils sprite; // useless for now

	Entity() : pos({ 0,0 }), color(WHITE) {};
	inline ~Entity() {};

	virtual void draw() {};
};
