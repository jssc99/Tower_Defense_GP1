#pragma once

#include "types.hpp"
#include "imgui_utils.hpp"

#define WHITE ImColor(1.f, 1.f, 1.f, 1.f)
#define BLACK ImColor(0.f, 0.f, 0.f, 1.f)
#define RED ImColor(1.f, 0.f, 0.f, 1.f);
#define GREEN ImColor(0.f, 1.f, 0.f, 1.f)
#define DARK_GREEN ImColor(0.f, 0.5f, 0.f, 1.f)
#define ORANGE ImColor(1.f, 0.5f, 0.f, 1.f)
#define YELLOW ImColor(1.f, 1.f, 0.f, 1.f)
#define VIOLET ImColor(0.5f, 0.f, 1.f, 1.f)
#define BLUE ImColor(0.f, 0.f, 1.f, 1.f)
#define CYAN ImColor(0.f, 0.8f, 1.f, 1.f)

#define SHY_WHITE ImColor(1.f, 1.f, 1.f, 0.5f)
#define SHY_BLACK ImColor(0.f, 0.f, 0.f, 0.5f)
#define SHY_RED ImColor(1.f, 0.f, 0.f, 0.5f);
#define SHY_GREEN ImColor(0.f, 1.f, 0.f, 0.5f)
#define SHY_ORANGE ImColor(1.f, 0.5f, 0.f, 0.5f)
#define SHY_VIOLET ImColor(0.5f, 0.f, 1.f, 0.5f)
#define SHY_BLUE ImColor(0.f, 0.f, 1.f, 0.5f)
#define SHY_LIGHT_BLUE ImColor(0.f, 0.3f, 0.8f, 0.5f)

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 704;

constexpr auto SQUARE_SIZE = 32;
constexpr auto H_SQUARE_SIZE = 16;
constexpr auto TOWER_SIZE = 24;
constexpr auto H_TOWER_SIZE = 12;

constexpr auto NB_SQUARES_COL = 40;
constexpr auto NB_SQUARES_ROW = 22;
constexpr auto MAX_NB_CHECKPOINTS = 22;
constexpr auto MAX_NB_TOWERS = 50;
constexpr auto MAX_NB_ENEMIES = 100;
constexpr auto NB_LEVELS = 10;

constexpr auto L_HEALTH_SIZE = 40;
constexpr auto H_HEALTH_SIZE = 5;

class Entity
{
public:
	float2 pos;
	ImGuiCol color;
	Texture sprite;

	Entity() : pos({ 0,0 }), color(WHITE) { this->sprite = ImGuiUtils::LoadTexture("assets/towerDefense_tile298.png"); };
	~Entity() { ImGuiUtils::UnloadTexture(this->sprite); };

	virtual void draw() { ImGuiUtils::DrawTextureEx(*ImGui::GetForegroundDrawList(), this->sprite, { this->pos.x, this->pos.y }); };
};