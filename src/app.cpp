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
														"ggggggggggggggggbbbbccpppppppppgggggggbb" +
														"ggggggggggggggggbbbbccpppppppppgggggggbb" +
														"spppppppgggggggggggggggggggggppgggggggbb" +
														"ppppppppgggggggggggggggggggggppgggggggbb" +
														"ggggggppggggggggbbgggggggggggppgggggggbb" +
														"ggggggppggggggggbbgggggggggggppgggggggbb" +
														"ggggggppggggggggbbgggggggggggppgggggggbb" +
														"ggggggppggggggggbbbbgggggggggppgggggggbb" +
														"ggggggppggggggggbbbbgggggggggppgggggggbb" +
														"ggggggppggggggggbbbbgggggggggppgggggggbb" +
														"ggggggppggggggggggbbbbgggggggppgggggggbb" +
														"ggggggppggggggggggbbbbgggggggppgggggggbb" +
														"bbggggpppppppppppppppppppppppppgggggggbb" +
														"bbggggpppppppppppppppppppppppppgggggggbb" +
														"bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
														"bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
														"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
														"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" };
		int id = 0;
		Checkpoint list[12] = {
			{++id, { 6,7 }, DOWN },
			{++id, { 16,7 }, RIGHT},
			{++id, { 16,30 }, UP},
			{++id, { 4,30 }, LEFT},
			{++id, { 4,21 }, STOP} };

		G.load(lvl[G.level], list, id);
	}
	// tower test
	{
		/*// do not use
		G.towers[0] = new Basic;
		G.towers[0]->setPos(G.grid.square[10][8].getPosCenter());
		G.towers[1] = new Explosive;
		G.towers[1]->setPos(G.grid.square[15][8].getPosCenter());
		G.towers[2] = new Quick;
		G.towers[2]->setPos(G.grid.square[15][28].getPosCenter());
		G.towers[3] = new Slow;
		G.towers[3]->setPos(G.grid.square[6][28].getPosCenter());
		G.towers[4] = new Slow;
		G.towers[4]->setPos(G.grid.square[3][28].getPosCenter());
		*/
		G.enemies[0] = new Enemy;
		G.enemies[0]->pos = G.grid.square[12][7].pos;
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
		ImGui::Text("mouse: %f, %f", mouse.x, mouse.y);
		ImGui::End();
	}
	if (this->debug)
		G.enemies[0]->pos = { mouse.x, mouse.y };
	else
		G.enemies[0]->pos = G.grid.square[12][7].pos;

	G.update();
	G.draw();
	if (this->debug)
		G.drawDebug();
}