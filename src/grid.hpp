#pragma once

#include "entities/square.hpp"

class Grid
{
public:
	Square square[NB_SQUARES_ROW][NB_SQUARES_COL];
	Checkpoint chkpList[MAX_NB_CHECKPOINTS];
	int nbCheckpoints;

	Grid();
	~Grid() {};

	void loadGrid(std::string seed);
	void loadCheckpoints(Checkpoint* checkpointList, int nbCheckpoint);
	void makePathLookGood();

	void draw();
	void drawGrid();
	void drawCheckpoints();

	float2 getSpawnPoint() const;
	Square* getSquare(float2 point);
};