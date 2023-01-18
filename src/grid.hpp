#pragma once

#include "entities/square.hpp"
#include "entities/castle.hpp"
#include "entities/checkpoint.hpp"

class Grid
{
public:
	Square squares[NB_SQUARES_ROW][NB_SQUARES_COL];
	Checkpoint checkpoints[MAX_NB_CHECKPOINTS];

	Grid();
	~Grid() {};

	void loadGrid(std::string seed);
	void loadCheckpoints(const Checkpoint* checkpointList, int nbCheckpoint, Castle* castle);

	void unloadGrid();

	void draw();
	void drawGrid();
	void drawCheckpoints();

	int getNbCheckpoints() const;
	float2 getSpawnPoint();
	Square* getSquare(float2 point);
	Square* getSquareXY(float2 XY);

private:
	float2 mSpawnPoint = STOP;
	int nNbCheckpoints = 0;

	void makePathLookGood();
};