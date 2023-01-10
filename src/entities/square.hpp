#pragma once

#include <string>

#include "../entity.hpp"
#include "checkpoint.hpp"

enum class Type : char
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
	Type type;

	Square();
	~Square() {};

	std::string getType() const;
	void setType(Type type);

	float2 getPosCenter() const;

	void draw() override;
};
