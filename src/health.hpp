#pragma once

class Health
{
public:
	float2 posCenter = { 0,0 };
	int life = 0;
	int maxLife = 0;

	Health() {};
	~Health() {};

	void draw() const;
};

inline void Health::draw() const
{
	ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
	ImDrawList* bgDrawlist = ImGui::GetBackgroundDrawList();
	fgDrawlist->AddRectFilled({ posCenter.x - L_HEALTH_SIZE / 2, posCenter.y - 30 }, { posCenter.x - L_HEALTH_SIZE / 2 + (life * L_HEALTH_SIZE) / maxLife, posCenter.y - H_HEALTH_SIZE - 30 }, DARK_GREEN);
	bgDrawlist->AddRectFilled({ posCenter.x - L_HEALTH_SIZE / 2, posCenter.y - 30 }, { posCenter.x + L_HEALTH_SIZE / 2, posCenter.y - H_HEALTH_SIZE - 30 }, RED);
}