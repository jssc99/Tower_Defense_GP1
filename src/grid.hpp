#pragma once

#include "square.hpp"

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 720;

class Grid
{
public:
	Square square[NB_SQUARES_COL][NB_SQUARES_ROW];

	Grid();
	~Grid() {};

	void drawGrid();
};