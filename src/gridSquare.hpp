#pragma once

constexpr auto NB_SQUARES_WIDTH = 30;
constexpr auto NB_SQUARES_HEIGHT = 18;

#include "entity.hpp"
#include "checkpoint.hpp"

class GridSquare : public Entity
{
public:
	int id;

	GridSquare() {};
	~GridSquare() {};
};

// Background tiles

class Background : public GridSquare
{
public:
	Background() {};
	~Background() {};
};

// Grass tiles (towers)

class Grass : public GridSquare
{
public:
	Grass() {};
	~Grass() {};
};

// Path tiles (enemies)

class Path : public GridSquare
{
public:
	bool isCheckpoint;
	Checkpoint checkpoint;

	Path(bool cp = false, int val = 0, direction dir = UP) : isCheckpoint(cp), checkpoint({val, dir}) {};
	~Path() {};
};