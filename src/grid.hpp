#pragma once

#include "entities/square.hpp"

constexpr auto NB_SQUARES_COL = 40;
constexpr auto NB_SQUARES_ROW = 22;

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 720;

class Grid
{
public:
	Square square[NB_SQUARES_ROW][NB_SQUARES_COL];

	Grid();
	~Grid() {};

	void drawGrid();
};