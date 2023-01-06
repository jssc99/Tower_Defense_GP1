#pragma once

#include "entities/square.hpp"

constexpr auto NB_SQUARES_COL = 40;
constexpr auto NB_SQUARES_ROW = 22;
constexpr auto MAX_NB_CHECKPOINTS = 22;

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
	void draw();
	void drawCheckpoints();
	float2 getSpawnPoint() const;
};