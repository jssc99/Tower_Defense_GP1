#include "grid.hpp"
#include "calc.hpp"

Grid::Grid()
{
	this->nbCheckpoints = 0;
	for (int i = 0; i < MAX_NB_CHECKPOINTS; i++)
		this->chkpList[i];
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			this->square[i][j].pos = { (float)j * SQUARE_SIZE, (float)i * SQUARE_SIZE };
}

void Grid::loadGrid(std::string seed)
{
	int id = 0;
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			if (seed[id])
				this->square[i][j].setType((Type)seed[id++]);
}

void Grid::loadCheckpoints(Checkpoint* checkpointList, int nbCheckpoints)
{
	this->nbCheckpoints = nbCheckpoints;
	for (int i = 0; i < nbCheckpoints; i++) {
		if (i + 1 == nbCheckpoints)
			this->square[(int)(checkpointList[i].pos.x)][(int)(checkpointList[i].pos.y)].setType(Type::CASTLE);
		else
			this->square[(int)(checkpointList[i].pos.x)][(int)(checkpointList[i].pos.y)].setType(Type::PATH);
		checkpointList[i].pos = this->square[(int)(checkpointList[i].pos.x)][(int)(checkpointList[i].pos.y)].pos;
		checkpointList[i].pos.y += SQUARE_SIZE;
		this->chkpList[i] = checkpointList[i];
	}
}

void Grid::draw()
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			this->square[i][j].draw();
}

// for debug purpose
void Grid::drawCheckpoints()
{
	for (int i = 0; i < this->nbCheckpoints; i++)
		this->chkpList[i].draw();
}

float2 Grid::getSpawnPoint() const
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			if (this->square[i][j].type == Type::SPAWN)
				return this->square[i][j].pos;
	return { 0,0 };
}