#include "app.hpp"

#include <stdio.h>

#define G this->game

App::App()
{
	// grid test
	{
		std::string lvl[1] = { std::string("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb") +
														"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
														"bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
														"bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
														"ggggggggggggggggbbbbccppppppppppggggggbb" +
														"ggggggggggggggggbbbbccppppppppppggggggbb" +
														"spppppppppppggggggggggggggggggppggggggbb" +
														"ppppppppppppggggggggggggggggggppggggggbb" +
														"ggppggppggggggggbbggggggggggggppggggggbb" +
														"ggppggppggggggggbbggggggggggggppggggggbb" +
														"ggppppppggggggggbbggggggggggggppggggggbb" +
														"ggppppppggggggggbbbbggggggggggppggggggbb" +
														"ggggggppppppggggbbbbggggggggggppggggggbb" +
														"ggggggppppppggggbbbbggggggggggppggggggbb" +
														"ggggggppggppggggggbbbbggggggggppggggggbb" +
														"ggggggppggppggggggbbbbggggggggppggggggbb" +
														"bbggppppppppppppppppppppppppppppggggggbb" +
														"bbggppppppppppppppppppppppppppppggggggbb" +
														"bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
														"bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
														"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
														"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" };
		int id = 0;
		Checkpoint list[12] = {
			{++id, { 6,7 }, DOWN },
			{++id, { 16,7 }, RIGHT},
			{++id, { 16,31 }, UP},
			{++id, { 4,31 }, LEFT},
			{++id, { 4,21 }, STOP} };

		G.load(lvl[G.level], list, id);
	}
	this->debug = false;
}

App::~App()
{
}

void App::Update()
{
	ImVec2 mouse = ImGui::GetMousePos();
	{
		ImGui::Begin("Tower");
		ImGui::Checkbox("Draw Grid", &this->debug);
		ImGui::Text("Money: %d", G.money);
		if (ImGui::Button("$$$ + 20"))
			G.money += 20;
		if (ImGui::Button("$$$ - 20"))
			G.money -= 20;
		for (int i = 0; i < MAX_NB_TOWERS; i++)
			if (G.towers[i]) {
				char name[20] = "";
				sprintf(name, "angle tower #%d", i);
				ImGui::SliderAngle(name, &G.towers[i]->angle, 0.f, 360.f);
			}
		ImGui::End();
	}
	G.update();
	G.draw();
	if (this->debug)
		G.drawDebug();
}