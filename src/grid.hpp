#pragma once

#include "entities/square.hpp"
#include "entities/castle.hpp"
#include "entities/checkpoint.hpp"

class Grid
{
public:
	Grid();
	inline ~Grid() {};

	void loadGrid(std::string seed);
	void loadCheckpoints(const Checkpoint* checkpointList, int nbCheckpoint, Castle* castle);
	void unloadGrid();

	void draw();
	void drawGrid();
	void drawCheckpoints();

	int getNbCheckpoints() const;
	Checkpoint* getCheckpoints();
	float2 getSpawnPoint();
	Square* getSquare(float2 point);
	Square* getSquareXY(int x, int y);

private:
	Square mSquares[NB_SQUARES_ROW][NB_SQUARES_COL];
	Checkpoint mCheckpoints[MAX_NB_CHECKPOINTS];

	float2 mSpawnPoint = STOP;
	int mNbCheckpoints = 0;

	void makePathLookGood();
};