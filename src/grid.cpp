#include "grid.hpp"

Grid::Grid()
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++) {
			this->square[i][j] = Square(Type::NONE);
			this->square[i][j].pos = { (float)j * SQUARE_SIZE + SQUARE_SIZE / 2.f, (float)i * SQUARE_SIZE + SQUARE_SIZE / 2.f - 1.f };
		}
}

void Grid::loadGrid(std::string seed)
{
	int id = 0;
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
		{
			if (seed[id])
				//this->square[i][j].setType(seed[id]);
			switch (seed[id++])
			{
			case 'n': // None, shouldn't happen
				this->square[i][j].setType(Type::NONE);
				break;
			case 'b': // Backg
				this->square[i][j].setType(Type::BACKGROUND);
				break;
			case 'g': // Grass
				this->square[i][j].setType(Type::GRASS);
				break;
			case 'p': // Path
				this->square[i][j].setType(Type::PATH);
				break;
			case 'c': // Castle
				this->square[i][j].setType(Type::CASTLE);
				break;
			case 's': // Spawn
				this->square[i][j].setType(Type::SPAWN);
				break;
			default:
				this->square[i][j].setType(Type::NONE);
				break;
			}
		}
}

void Grid::loadCheckpoints(Checkpoint* checkpointList)
{
	int size = sizeof(checkpointList) / sizeof(checkpointList[0]);
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			for (int k = 0; k < size; k++)
				if (checkpointList[k].pos.x == this->square[i][j].pos.x && checkpointList[k].pos.y == this->square[i][j].pos.y)
					this->square[i][j].setType(Type::PATH, true, checkpointList[k].id, checkpointList[k].newDirection);
}

void Grid::drawGrid()
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			this->square[i][j].drawEntity();
}

float2 Grid::getSpawnPoint() const
{
	for (int i = 0; i < NB_SQUARES_COL; i++)
		for (int j = 0; j < NB_SQUARES_ROW; j++)
			if (this->square[i][j].type == Type::SPAWN)
				return this->square[i][j].pos;
	return { 0,0 };
}

float2* Grid::getCheckpoints() const
{
	float2* chkp = new float2;
	for (int i = 0; i < NB_SQUARES_COL; i++)
		for (int j = 0; j < NB_SQUARES_ROW; j++)
			if (this->square[i][j].checkpoint.id != 0)
				chkp[this->square[i][j].checkpoint.id] = this->square[i][j].checkpoint.pos;
	return chkp;
}
