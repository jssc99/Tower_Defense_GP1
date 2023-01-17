#pragma once

#include "menu.hpp"

struct level
{
	int id;
	std::string seed;
	int nbCheckpoints;
	Checkpoint checkpointList[MAX_NB_CHECKPOINTS];
};

class Game
{
public:
	Menu menu;
	Grid grid;
	Tower* towers[MAX_NB_TOWERS];
	Enemy* enemies[MAX_NB_ENEMIES];
	Castle castle;
	float enSpwTimer = 0;

	level lvl[NB_LEVELS];
	int money;
	int wave;

	Game();
	~Game();

	void loadLvl(int lvl);
	void update();
	void draw();
	void drawDebug();

	int getFreeEnemySpotId();
	int getFreeTowerSpotId();

	void spawnEnemy(Type_Enemy type);

private:
	void updateEnemies();
	void updateTowers();

	void drawEnemies();
	void drawTowers();

	void placeTower(Square* s);

};