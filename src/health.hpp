#pragma once

class Health
{
public:
	float2 posCenter = { 0,0 };
	int life = 0;
	int maxLife = 0;

	Health() {};
	~Health() {};

	void draw(float L, float H) const;
};

inline void Health::draw(float L, float H) const
{
	ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
	fgDrawlist->AddRectFilled({ posCenter.x - L / 2, posCenter.y - 30 }, { posCenter.x - L / 2 + (life * L) / maxLife, posCenter.y -H - 30 }, DARK_GREEN);
	fgDrawlist->AddRectFilled({ posCenter.x - L / 2 + (life * L) / maxLife, posCenter.y - 30 }, { posCenter.x + L / 2, posCenter.y -H - 30 }, RED);
}