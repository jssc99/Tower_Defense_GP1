#pragma once

#include "grid.hpp"
#include "entities/enemy.hpp"
#include "entities/castle.hpp"
#include "entities/towers/slow_tower.hpp"
#include "entities/towers/basic_tower.hpp"
#include "entities/towers/quick_tower.hpp"
#include "entities/towers/explosive_tower.hpp"


class Game
{
public:
	Grid grid;
	Castle castle;
	Tower* towers[50];
	Enemy* enemies[50];

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

	void mDrawEnemies();
	void mDrawTowers();
};
