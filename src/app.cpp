#include "app.hpp"

#include <stdio.h>

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
	this->grid.loadGrid(lvl1);
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
	this->grid.loadCheckpoints(list, id);


	//enemy test
	e.pos = this->grid.getSpawnPoint();
	e.moveSpeed = 1.f;
	e.attackDmg = 50;
	e.direction = RIGHT;

	//castle test
	c.health = 200;
}

App::~App()
{
}

void App::Update()
{	
	{
		ImGui::Begin("Tower");
		ImGui::Text("Enemy pos = %f, %f", e.pos.x, e.pos.y);
		ImGui::SliderFloat("Enemy ms", &e.moveSpeed, 0.1f, 10.0f);
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
		ImGui::Text("\n");
		ImGui::Text("checkpoint[0] pos %f, %f", grid.chkpList[0].pos.x, grid.chkpList[0].pos.y);
		ImGui::Text("checkpoint[0] id %d", grid.chkpList[0].id);
		ImGui::Text("checkpoint[1] id %d", grid.chkpList[1].id);
		ImGui::Text("castle hp = %d", c.health);

		ImGui::End();
	}
	this->grid.draw();

	e.draw();
	e.pos += e.direction * e.moveSpeed;

	//checkpoint test
	for (int i = 0; i < grid.nbCheckpoints; ++i)
	{
		grid.chkpList[i].draw();
		if (e.pos.x >= grid.chkpList[i].pos.x - 5.f && e.pos.x <= grid.chkpList[i].pos.x + 5.f && e.pos.y >= grid.chkpList[i].pos.y - 5.f && e.pos.y <= grid.chkpList[i].pos.y + 5.f && grid.chkpList[i].id == e.checkId)
		{
			e.direction = grid.chkpList[i].newDirection;
			e.checkId++;
			//castle test
			if (i+1 == grid.nbCheckpoints)//==last checkpoint(castle)
			{
				c.health -= e.attackDmg;
			}
		}
	}
	c.drawHealth();

}