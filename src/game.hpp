#pragma once

#include "menu.hpp"

struct level
{
	int id = 0;
	std::string seed;
	int nbCheckpoints = 0;
	Checkpoint checkpointList[MAX_NB_CHECKPOINTS];
	int nbWaves = 0;
	std::string wave[100];
};

class Game
{
public:
	Menu menu;
	Grid grid;
	Tower* towers[MAX_NB_TOWERS];
	Enemy* enemies[MAX_NB_ENEMIES];
	Castle* castle = nullptr;

	float enSpawnTimer = 0.f;

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

	void spawnEnemy(Type_Enemy type);

private:
	int mCurrentLevelId = 0;
	int mWaveAdvancement = 0;
	float mWaveCooldown = 0;

	void updateInGame();
	void updateWave();
	void updateEnemies();
	void updateTowers();

	void drawEnemies() const;
	void drawTowers() const;

	bool isWaveDead();

	void placeTower(Square* s);
};