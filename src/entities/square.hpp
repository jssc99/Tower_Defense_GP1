#pragma once

#include <string>

#include "../entity.hpp"
#include "checkpoint.hpp"

constexpr float SQUARE_SIZE = 32.f;

enum class Type : char
{
	NONE = 'n',
	BACKGROUND = 'b',
	GRASS = 'g',
	PATH = 'p',
	CASTLE = 'c',
	SPAWN = 's'
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
	// maybe useless
	Square(Type type, bool isCheckpoint = 0, int chkpId = 0, float2 newDirChkp = { 0,0 });
	~Square() {};

	std::string getType() const;

	// also used to set checkpoint
	void setType(Type type, bool isCheckpoint = 0, int chkpId = 0, float2 newDirChkp = { 0,0 });
	virtual void drawEntity();

private:
	void setCheckpoint(int id, float2 newDir, float2 pos);
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