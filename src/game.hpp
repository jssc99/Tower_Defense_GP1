#pragma once

#include "menu.hpp"

struct level
{
	int id = 0;
	std::string seed;
	int nbCheckpoints = 0;
	Checkpoint checkpointList[MAX_NB_CHECKPOINTS];
};

class Game
{
public:
	Menu menu;
	Grid grid;
	Tower* towers[MAX_NB_TOWERS];
	Enemy* enemies[MAX_NB_ENEMIES];
	Castle* castle = nullptr;

	level lvl[NB_LEVELS];
	int money = 0;
	int wave = 0;
	int towerPlaced = 0;

	bool closeGame = false;

	Game();
	~Game();

	void loadLvl(int lvl);
	void unloadLvl();
	void update();
	void draw();
	void drawDebug();

	int getFreeEnemySpotId() const;
	int getFreeTowerSpotId() const;

private:
	int mCurrentLevelId = 0;

	void updateEnemies();
	void updateTowers();

	void drawEnemies() const;
	void drawTowers() const;

	void placeTower(Square* s);
};