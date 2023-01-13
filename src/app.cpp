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
														"spppppppggggggggggggggggggggggppggggggbb" +
														"ppppppppggggggggggggggggggggggppggggggbb" +
														"ggggggppggggggggbbggggggggggggppggggggbb" +
														"ggggggppggggggggbbggggggggggggppggggggbb" +
														"ggggggppggggggggbbggggggggggggppggggggbb" +
														"ggggggppggggggggbbbbggggggggggppggggggbb" +
														"ggggggppggggggggbbbbggggggggggppggggggbb" +
														"ggggggppggggggggbbbbggggggggggppggggggbb" +
														"ggggggppggggggggggbbbbggggggggppggggggbb" +
														"ggggggppggggggggggbbbbggggggggppggggggbb" +
														"bbggggppppppppppppppppppppppppppggggggbb" +
														"bbggggppppppppppppppppppppppppppggggggbb" +
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
		ImGui::End();
	}
	G.update();
	G.draw();
	if (this->debug)
		G.drawDebug();
}