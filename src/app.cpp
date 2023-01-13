#include "app.hpp"

#include <stdio.h>

#define G this->game

App::App()
{
	// grid test
	std::string lvl1 = std::string("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")+
								   "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
								   "bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
								   "bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
								   "ggggggggggggggggbbbbccpppppppppgggggggbb" +
								   "ggggggggggggggggbbbbccpppppppppgggggggbb" +
								   "ppppppppgggggggggggggggggggggppgggggggbb" +
								   "spppppppgggggggggggggggggggggppgggggggbb" +
								   "ggggggppggggggggbbgggggggggggppgggggggbb" +
								   "ggggggppggggggggbbgggggggggggppgggggggbb" +
								   "ggggggppggggggggbbgggggggggggppgggggggbb" +
								   "ggggggppggggggggbbbbgggggggggppgggggggbb" +
								   "ggggggppppppppppppppgggggggggppgggggggbb" +
								   "ggggggppppppppppppppgggggggggppgggggggbb" +
								   "ggggggppggggggggggppbbgggggggppgggggggbb" +
								   "ggggggppggggggggggppbbgggggggppgggggggbb" +
								   "bbggggpppppppppppppppppppppppppgggggggbb" +
								   "bbggggpppppppppppppppppppppppppgggggggbb" +
								   "bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
								   "bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
								   "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
								   "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
	int id = 0;
	Checkpoint list[9] = {
		{++id, { 6,7 }, DOWN },
		{++id, { 16,7 }, RIGHT},
		{++id, { 16,19}, UP},
		{++id, { 12,19}, LEFT},
		{++id, { 12,7}, DOWN},
		{++id, { 16,7 }, RIGHT},
		{++id, { 16,30 }, UP},
		{++id, { 4,30 }, LEFT},
		{++id, { 4,21 }, STOP}
	};
	G.load(lvl1, list, id);
	this->debug = false;
	G.money += 100;
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
		if (ImGui::Button("Soldier"))
		{
			int id = G.getFreeEnemySpotId();
			G.enemies[id] = new Soldier;
			G.enemies[id]->pos = G.grid.getSpawnPoint();
		}
		if (ImGui::Button("Healer"))
		{
			int id = G.getFreeEnemySpotId();
			G.enemies[id] = new Healer;
			G.enemies[id]->pos = G.grid.getSpawnPoint();
		}
		if (ImGui::Button("Knight"))
		{
			int id = G.getFreeEnemySpotId();
			G.enemies[id] = new Knight;
			G.enemies[id]->pos = G.grid.getSpawnPoint();
		}
		ImGui::Text("Castle health and max health: %d, %d", G.castle.healthSystem.health, G.castle.healthSystem.maxHealth);
		ImGui::Text("mouse: %f, %f", mouse.x, mouse.y);
		ImGui::End();
	}

	G.update();
	G.draw();
	if (this->debug)
		G.drawDebug();
}