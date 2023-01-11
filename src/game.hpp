#pragma once

#include "grid.hpp"
#include "entities/enemy.hpp"
#include "entities/towers/slow_tower.hpp"
#include "entities/towers/basic_tower.hpp"
#include "entities/towers/quick_tower.hpp"
#include "entities/towers/explosive_tower.hpp"

struct purchaseMenu
{
	Tower* tow[4];
};

class Game
{
public:
	Grid grid;
	Tower* towers[50];
	Enemy* enemies[50];

	purchaseMenu purchaseMenu;

	int level;
	int money;
	int wave;

	Game();
	~Game();

	void load(std::string seed, Checkpoint* checkpointList, int nbCheckpoint);
	void update();
	void draw();

private:
	void mUpdateEnemies();
	void mUpdateTowers();
	void mUpdateMenu();

	void mDrawEnemies();
	void mDrawTowers();
	void mDrawMenu();
};