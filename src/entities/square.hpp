#pragma once

#include <string>

#include "../entity.hpp"

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
	Square();
	~Square();

	void setType(Type_Square type);
	Type_Square getType();

	float2 getPosCenter() const;

	bool canPlaceTower() const;
	void cantHaveTower();

	void draw() override;
	void drawPos();

private:
	Type_Square mType;
	Texture mDecor;
	bool mHasDecor = false;
	bool mCanHaveTower = false;
};