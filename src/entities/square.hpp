#pragma once

#include <string>

#include "../entity.hpp"
#include "checkpoint.hpp"

enum class Type_Square : char
{
	NONE = 'n',
	BACKGROUND = 'b',
	GRASS = 'g',
	PATH = 'p',
	CASTLE = 'c',
	SPAWN = 's'
};

class Square : public Entity
{
public:
	Type_Square type;
	bool canHaveTower;

	Square();
	~Square() {};

	void setType(Type_Square type);

	float2 getPosCenter() const;

	bool canPlaceTower();

	void draw() override;
	void drawPos();
};