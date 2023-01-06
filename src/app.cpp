#include "app.hpp"

#include <stdio.h>

App::App()
{
	// grid test
	std::string lvl1 =  std::string("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")+
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
												"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" ;
	this->grid.loadGrid(lvl1);
	int id = 0;
	Checkpoint list[12] ={
	    {++id, { 6,7 }, DOWN },
		{++id, { 16,7 }, RIGHT},
		{++id, { 16,30 }, UP},
		{++id, { 4,30 }, LEFT},
		{++id, { 4,21 }, STOP} };
	this->grid.loadCheckpoints(list, id);
}

App::~App()
{
}

void App::Update()
{
	{
		ImGui::Begin("Tower");
		/*
		ImGui::Text("e.pos = %f, %f", e.pos.x, e.pos.y);
		ImGui::SliderFloat("move speed = ", &e.moveSpeed, 0.1f, 10.f);
		if (ImGui::Button("Right"))
			e.direction = RIGHT;
		if (ImGui::Button("Left"))
			e.direction = LEFT;
		if (ImGui::Button("Up"))
			e.direction = UP;
		if (ImGui::Button("Down"))
			e.direction = DOWN;
		if (ImGui::Button("Stop"))
			e.direction = STOP;
			*/

		ImGui::End();
	}
	this->grid.draw();
	this->grid.drawCheckpoints();
}