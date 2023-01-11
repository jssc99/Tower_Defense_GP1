#include <imgui.h>

#include "enemy.hpp"

void Enemy::draw()
{
	ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
	fgDrawlist->AddCircleFilled({ pos.x, pos.y }, 10, ImColor(1.f, 0.f, 0.f));
}

