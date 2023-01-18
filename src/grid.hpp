#pragma once

#include "entities/square.hpp"
#include "entities/castle.hpp"

class Grid
{
public:
	Square square[NB_SQUARES_ROW][NB_SQUARES_COL];
	Checkpoint chkpList[MAX_NB_CHECKPOINTS];
	float2 spawnP = STOP;
	int nbCheckpoints = 0;

	Grid();
	~Grid() {};

	void loadGrid(std::string seed);
	void unloadGrid();
	void loadCheckpoints(const Checkpoint* checkpointList, int nbCheckpoint, Castle* castle);
	void makePathLookGood();

	void draw();
	void drawGrid();
	void drawCheckpoints();

	float2 getSpawnPoint();
	Square* getSquare(float2 point);
};