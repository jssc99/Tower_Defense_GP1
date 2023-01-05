#include "grid.hpp"

Grid::Grid()
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++) {
			this->square[i][j] = Square(NONE);
			this->square[i][j].pos = { (float)j * SQUARE_SIZE + SQUARE_SIZE / 2.f, (float)i * SQUARE_SIZE + SQUARE_SIZE / 2.f - 1.f };
		}
}

void Grid::drawGrid()
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			this->square[i][j].drawEntity();
}

float2 Grid::getSpawnPoint()
{
	for (int i = 0; i < NB_SQUARES_COL; i++)
		for (int j = 0; j < NB_SQUARES_ROW; j++)
			if (this->square[i][j].type == SPAWN)
				return this->square[i][j].pos;
	return { 0,0 };
}
