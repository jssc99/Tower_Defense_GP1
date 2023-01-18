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
	Texture decor;

	bool hasDecor = false;
	bool canHaveTower = false;

	Square();
	~Square();

	void setType(Type_Square type);

	float2 getPosCenter() const;

	bool canPlaceTower() const;

	void draw() override;
	void drawPos();
};