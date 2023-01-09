#include "app.hpp"

#include <stdio.h>

App::App()
{
	// grid test
	{
		std::string lvl1 = std::string("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb") +
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
												   "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
		this->grid.loadGrid(lvl1);
		int id = 0;
		Checkpoint list[12] = {
			{++id, { 6,7 }, DOWN },
			{++id, { 16,7 }, RIGHT},
			{++id, { 16,30 }, UP},
			{++id, { 4,30 }, LEFT},
			{++id, { 4,21 }, STOP} };
		this->grid.loadCheckpoints(list, id);
	}
	// tower test
	{
		this->towers[0] = new Basic;
		this->towers[0]->setPos(this->grid.square[10][8].getPosCenter());
		this->towers[1] = new Explosive;
		this->towers[1]->setPos(this->grid.square[15][8].getPosCenter());
		this->towers[2] = new Quick;
		this->towers[2]->setPos(this->grid.square[15][28].getPosCenter());
		this->towers[3] = new Slow;
		this->towers[3]->setPos(this->grid.square[6][28].getPosCenter());

		this->enemies[0] = new Enemy;
		this->enemies[0]->pos = this->grid.square[12][7].pos;
	}
}

App::~App()
{
}

void App::Update()
{
	{
		ImGui::Begin("Tower");
		ImGui::End();
	}

	ImVec2 mouse = ImGui::GetMousePos();
	this->enemies[0]->pos = { mouse.x, mouse.y };

	this->grid.draw();
	this->grid.drawCheckpoints();
	this->towers[0]->update(this->enemies, 1);
	this->towers[1]->update(this->enemies, 1);
	this->towers[2]->update(this->enemies, 1);
	this->towers[3]->update(this->enemies, 1);
	this->towers[0]->draw();
	this->towers[1]->draw();
	this->towers[2]->draw();
	this->towers[3]->draw();
	this->enemies[0]->draw();
}