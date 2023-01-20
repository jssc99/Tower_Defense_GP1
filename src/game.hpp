#pragma once

#include "menu.hpp"

struct Level
{
	int id = 0;
	std::string seed;
	int nbCheckpoints = 0;
	Checkpoint checkpointList[MAX_NB_CHECKPOINTS];
	int nbWaves = 0;
	std::string wave[MAX_NB_WAVES];
};

class Game
{
public:
	Level lvl[NB_LEVELS];

	bool closeGame = false;

	float gameSpeed = 1.f;

	Game();
	~Game();

	void launchLvl(int lvl);
	void unloadLvl();

	void update();
	void draw();

	//debug functions
	void drawDebug();
	void addMoney(int m);				// useless outside of debug
	void spawnEnemy(Type_Enemy type);	// should be private but is usefull for debug

private:
	Menu mMenu;
	Grid mGrid;
	Tower* mTowers[MAX_NB_TOWERS];
	Enemy* mEnemies[MAX_NB_ENEMIES];
	Castle* mCastle = nullptr;

	int mWaveAdvancement = 0;
	float mWaveCooldown = 0;
	float mEnemySpawnTimer = 0.f;

	int mCurrentLevelId = 0;

	int mMoney = 0;
	int mWave = 0;
	int mTowerPlaced = 0;

	void updateInGame();
	void updateWave();
	void updateEnemies();
	void updateTowers();

	void drawEnemies() const;
	void drawTowers() const;
	void drawCastle() const;

	int getFreeEnemySpotId() const;
	int getFreeTowerSpotId() const;

	bool isWaveDead() const;
	void placeTower(Square* s);
};