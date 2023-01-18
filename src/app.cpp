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
		int waves = 0;
		G.lvl[0].wave[waves++] = "sssssssssssssssssske";
		G.lvl[0].wave[waves++] = "sssskksssssssskksssske";
		G.lvl[0].wave[waves++] = "sssskkhssssssskkhssssske";
		G.lvl[0].wave[waves++] = "sssskkkkhssssskkkkhsssske";
		G.lvl[0].wave[waves++] = "ssskkkkkkhssshkkkkhssssske";
		G.lvl[0].wave[waves++] = "ssskkkkkkhssshkkkkhsssssske";
		G.lvl[0].wave[waves++] = "ssskkkkkkhssshkkkkkkhssssske";
		G.lvl[0].wave[waves++] = "ssskkkkkkkhssshkkkkkkhssssske";
		G.lvl[0].wave[waves++] = "ssshkkkkkkhssshhhkkkkkhssssske";
		G.lvl[0].wave[waves++] = "ssshhkkkkkkhssshhhkkkkhsssssske";
		G.lvl[0].nbWaves = waves;
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
		int waves = 0;
		G.lvl[1].wave[waves++] = "ssssssssssssssssssk";
		G.lvl[1].wave[waves++] = "sssskksssssssskksssske";
		G.lvl[1].wave[waves++] = "sssskkhssssssskkhssssske";
		G.lvl[1].wave[waves++] = "sssskkkkhssssskkkkhsssske";
		G.lvl[1].wave[waves++] = "ssskkkkkkhssshkkkkhssssske";
		G.lvl[1].wave[waves++] = "ssskkkkkkhssshkkkkhsssssske";
		G.lvl[1].wave[waves++] = "ssskkkkkkhssshkkkkkkhssssske";
		G.lvl[1].wave[waves++] = "ssskkkkkkkhssshkkkkkkhssssske";
		G.lvl[1].wave[waves++] = "ssshkkkkkkhssshhhkkkkkhssssske";
		G.lvl[1].wave[waves++] = "ssshhkkkkkkhssshhhkkkkhsssssske";
		G.lvl[1].nbWaves = waves;
	}
}

App::~App()
{
}

void App::Update()
{
	if (ImGui::IsKeyPressed(ImGuiKey_C, false))
		this->mDebugMenu = !this->mDebugMenu;

	if (this->mDebugMenu)
	{
		ImGui::Begin("Tower");
		ImGui::Checkbox("Draw Grid", &this->mDrawDebug);
		// ImGui::Text("mouse: %.0f, %.0f", ImGui::GetMousePos().x, ImGui::GetMousePos().y);
		if (ImGui::Button("$$$ + 20")) G.addMoney(20);
		if (ImGui::Button("$$$ - 20")) G.addMoney(-20);
		if (ImGui::Button("Soldier"))
			G.spawnEnemy(Type_Enemy::SOLDIER);
		if (ImGui::Button("Healer"))
			G.spawnEnemy(Type_Enemy::HEALER);
		if (ImGui::Button("Knight"))
			G.spawnEnemy(Type_Enemy::KNIGHT);
		ImGui::End();
	}

	G.update();
	G.draw();
	if (this->mDrawDebug) G.drawDebug();
	this->closeApp = G.closeGame;
}