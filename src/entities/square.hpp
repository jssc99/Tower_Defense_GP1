#pragma once

#include <string>

#include "../entity.hpp"
#include "../checkpoint.hpp"
#include "../checkpoint.hpp"

constexpr float SQUARE_SIZE = 32.f;

enum Type
{
	NONE,
	BACKGROUND,
	GRASS,
	PATH,
	CASTLE,
	SPAWN
};

static int _id = 0;

class Square : public Entity
{
public:
	int id;
	bool canPlaceTower;
	bool hasCheckpoint;
	Type type;
	ImGuiCol color;
	Checkpoint checkpoint;

	Square();
	Square(Type type);
	//creator for checkpoint pathway TODO
	~Square() {};

	std::string getType();
	void setType(Type type);
	virtual void drawEntity();
};





/*
// Background tiles
class Background : public Square
{
public:
	Background() {};
	~Background() {};

	void drawEntity();
};

// Grass tiles (towers)
class Grass : public Square
{
public:
	Grass() {};
	~Grass() {};

	void drawEntity();
};

// Path tiles (enemies)
class Path : public Square
{
public:
	bool hasCheckpoint;
	Checkpoint checkpoint;

	Path(bool cp = false, int val = 0, direction dir = UP) : hasCheckpoint(cp), checkpoint({val, dir}) {};
	~Path() {};

	void drawEntity();
};*/