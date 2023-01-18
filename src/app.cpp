#include "app.hpp"

#include <stdio.h>

#define G this->game

App::App()
{
	{ // level 1
		G.lvl[0].id = 1;
		G.lvl[0].seed = { std::string("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb") +
									  "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
									  "bbbbbggggggbbbbbbbbbbbbbggggggggbbbbbbbb" +
									  "bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
									  "bbbggggggggggggbbbbbccppppppppppggbbbbbb" +
									  "bbgggggggggggggbbbbbccppppppppppggbbbbbb" +
									  "spppppppgggggggbbbbbggggggggggppgggbbbbb" +
									  "ppppppppggggggbbbbbgggggggggggppggggbbbb" +
									  "ggggggppgggggbbbbbggggggggggggppggggbbbb" +
									  "ggggggppgggggbbbbbggggggggggggppggggbbbb" +
									  "ggggggppgggggbbbbbbgggggggggggppggggbbbb" +
									  "ggggggppggggggbbbbbbggggggggggppggggbbbb" +
									  "bgggggppgggggggbbbbbbgggggggggppggggbbbb" +
									  "bgggggppggggggggbbbbbgggggggggppggggbbbb" +
									  "bbggggppgggggggggbbbbbggggggggppggggbbbb" +
									  "bbggggppggggggggggbbbbggggggggppggggbbbb" +
									  "bbggggppppppppppppppppppppppppppgggbbbbb" +
									  "bbbgggppppppppppppppppppppppppppgggbbbbb" +
									  "bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
									  "bbbbbbbbbbggggggbbbbbbbbggggggbbbbbbbbbb" +
									  "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
									  "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" };
		int id = 0;
		G.lvl[0].checkpointList[id++] = { id + 1, { 6,7 }, DOWN };
		G.lvl[0].checkpointList[id++] = { id + 1, { 16,7 }, RIGHT };
		G.lvl[0].checkpointList[id++] = { id + 1, { 16,31 }, UP };
		G.lvl[0].checkpointList[id++] = { id + 1, { 4,31 }, LEFT };
		G.lvl[0].checkpointList[id++] = { id + 1, { 4,21 }, STOP };
		G.lvl[0].nbCheckpoints = id;
	}
	{ // level 2
		G.lvl[1].id = 2;
		G.lvl[1].seed = { std::string("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb") +
									  "bbbbbgggggggbbbbbbbbbbbggggggggbbbbbbbbb" +
									  "bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
									  "bggggggggggggggggggggggggggggggggggbbbbb" +
									  "gggggggggggggggggggggggggggggggggggbbbbb" +
									  "spppppppppppppppppppppppppppppggggggbbbb" +
									  "ppppppppppppppppppppppppppppppggggggbbbb" +
									  "bbbgggbbbbbbbbbbbbbbbbbbbbbbppbbbbbbbbbb" +
									  "bbbgggbbbbbbbbbbbbbbbbbbbbbbppbbbbbbbbbb" +
									  "bbbgggppppppppppppppppppppppppppppccbbbb" +
									  "bbbgggppppppppppppppppppppppppppppccbbbb" +
									  "bbggggppggggggggggggggggggbbppbggggbbbbb" +
									  "bbggggppgggggggggggggggggggbppgggggbbbbb" +
									  "bbggggppggggggggggggggggggggppgggggbbbbb" +
									  "bbggggppggggggggggggggggggggppgggggbbbbb" +
									  "bbbgggppppppppppppppppppppppppgggggbbbbb" +
									  "bbbgggppppppppppppppppppppppppgggggbbbbb" +
									  "bbbbggggggggggggggggggggggggggggggbbbbbb" +
									  "bbbbbbbbbbbbbbbbbbbbbbgggggggggbbbbbbbbb" +
									  "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
									  "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
									  "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" };
		int id = 0;
		G.lvl[1].checkpointList[id++] = { id + 1, { 5,29 }, DOWN };
		G.lvl[1].checkpointList[id++] = { id + 1, { 15,29 }, LEFT };
		G.lvl[1].checkpointList[id++] = { id + 1, { 15,7 }, UP };
		G.lvl[1].checkpointList[id++] = { id + 1, { 9,7 }, RIGHT };
		G.lvl[1].checkpointList[id++] = { id + 1, { 9,35 }, STOP };
		G.lvl[1].nbCheckpoints = id;
	}
}

App::~App()
{
}

void App::Update()
{
	{
		ImGui::Begin("Tower");
		ImGui::Checkbox("Draw Grid", &this->debug);
		ImGui::Text("mouse: %.0f, %.0f", ImGui::GetMousePos().x, ImGui::GetMousePos().y);
		if (ImGui::Button("$$$ + 20")) G.money += 20;
		if (ImGui::Button("$$$ - 20"))  G.money -= 20;
		if (ImGui::Button("unload lvl")) {
			G.unloadLvl();
			G.menu.load(Type_Menu::MAIN);
		}
		if (ImGui::Button("Soldier"))
			G.spawnEnemy(Type_Enemy::SOLDIER);
		if (ImGui::Button("Healer"))
			G.spawnEnemy(Type_Enemy::HEALER);
		if (ImGui::Button("Knight"))
			G.spawnEnemy(Type_Enemy::KNIGHT);
		if (G.castle) {
			ImGui::Text("Castle health and max health: %d, %d", G.castle->health.life, G.castle->health.maxLife);
			ImGui::Text("Castle pos = %f, %f", G.castle->pos.x, G.castle->pos.y);
		}
		ImGui::End();
	}
	G.update();
	G.draw();
	G.enSpwTimer += ImGui::GetIO().DeltaTime;
	if (G.enSpwTimer > 300 * ImGui::GetIO().DeltaTime)
		G.spawnEnemy(Type_Enemy::HEALER);
	if (this->debug) G.drawDebug();
	this->closeApp = G.closeGame;
}