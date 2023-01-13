#pragma once

class HealthSystem
{
public:
	int maxHealth;
	int health;

	HealthSystem() {};
	~HealthSystem() {};

	/*void draw()
	{
		ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
		fgDrawlist->AddRectFilled({ pos.x, pos.y }, { pos.x, pos.y}, ImColor(0.f, 1.f, 0.f));
	}
	*/
};