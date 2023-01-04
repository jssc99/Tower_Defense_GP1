#include "grid.hpp"

Grid::Grid()
{
	for (int i = 0; i < NB_SQUARES_COL; i++)
		for (int j = 0;  j < NB_SQUARES_ROW; j++)
			this->square[i][j].pos = { (float)i * SQUARE_SIZE + SQUARE_SIZE / 2.f, (float)j * SQUARE_SIZE + SQUARE_SIZE / 2.f };
}

void Grid::drawGrid()
{
	for (int i = 0; i < NB_SQUARES_COL; i++)
		for (int j = 0; j < NB_SQUARES_ROW; j++)
			this->square[i][j].drawEntity();
}