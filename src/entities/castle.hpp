#pragma once

#include "../entity.hpp"
#include "../health.hpp"

#define CASTLE_LIFE_POS { H_WIDTH + 180, HEIGHT /*- 30 + 30*/ } // (+30, off center health bar)

class Castle : public Entity
{
public:
	Health health;

	inline Castle() {
		this->health.posCenter = CASTLE_LIFE_POS;
		this->health.maxLife = 100;
		this->health.life = health.maxLife;
		this->loadTexture("assets/castle.png");
	};
	inline ~Castle() {};

	inline void draw();

	inline bool isDead() const { return this->health.life <= 0; };
};

void Castle::draw()
{
	ImGuiUtils::DrawTextureEx(*ImGui::GetBackgroundDrawList(), this->sprite, this->pos, { 0.5f,0.5f });
}