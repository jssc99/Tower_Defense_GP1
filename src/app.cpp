#include "app.hpp"

#include <stdio.h>

#define G this->game

App::App()
{
	// grid test
	{
		G.lvl[0].id = 1;
		G.lvl[0].seed = { std::string("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb") +
												   "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
												   "bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
												   "bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
												   "ggggggggggggggggbbbbccppppppppppggggbbbb" +
												   "ggggggggggggggggbbbbccppppppppppggggbbbb" +
												   "spppppppggggggggbbggggggggggggppggggbbbb" +
												   "ppppppppggggggggbbggggggggggggppggggbbbb" +
												   "ggggggppggggggggbbggggggggggggppggggbbbb" +
												   "ggggggppggggggggbbggggggggggggppggggbbbb" +
												   "ggggggppggggggggbbggggggggggggppggggbbbb" +
												   "ggggggppggggggggbbbbggggggggggppggggbbbb" +
												   "ggggggppggggggggbbbbggggggggggppggggbbbb" +
												   "ggggggppggggggggbbbbggggggggggppggggbbbb" +
												   "ggggggppggggggggggbbbbggggggggppggggbbbb" +
												   "ggggggppggggggggggbbbbggggggggppggggbbbb" +
												   "bbggggppppppppppppppppppppppppppggggbbbb" +
												   "bbggggppppppppppppppppppppppppppggggbbbb" +
												   "bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
												   "bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
												   "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
												   "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" };
		int id = 0;
		int _id = 0;
		G.lvl[0].checkpointList[_id++] = { ++id, { 6,7 }, DOWN };
		G.lvl[0].checkpointList[_id++] = { ++id, { 16,7 }, RIGHT };
		G.lvl[0].checkpointList[_id++] = { ++id, { 16,31 }, UP };
		G.lvl[0].checkpointList[_id++] = { ++id, { 4,31 }, LEFT };
		G.lvl[0].checkpointList[_id++] = { ++id, { 4,21 }, STOP };
		G.lvl[0].nbCheckpoints = id;

	}
	this->debug = false;
}

App::~App()
{
}

void App::Update()
{
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
				ImGui::SliderAngle(name, &G.towers[i]->turret.angle, 0.f, 360.f);
			}
		if (ImGui::Button("load lvl1"))
			G.loadLvl(1);

		ImGui::Text("Castle health and max health: %d, %d", G.castle.health.life, G.castle.health.maxLife);
		ImGui::Text("Castle pos = %f, %f", G.castle.pos.x, G.castle.pos.y);
		ImGui::Text("enSpwTimer = %f", G.enSpwTimer);

		ImGui::End();
	}
	G.update();
	G.draw();
	G.enSpwTimer += ImGui::GetIO().DeltaTime;
	if (G.enSpwTimer > 300 * ImGui::GetIO().DeltaTime)
	{
		G.enSpwTimer = 0;
		G.spawnEnemy(Type_Enemy::HEALER);
		//TODO: spawn enemies
	}
	if (this->debug)
		G.drawDebug();
}