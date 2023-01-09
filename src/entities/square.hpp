#pragma once

#include <string>

#include "../entity.hpp"
#include "checkpoint.hpp"

constexpr auto SQUARE_SIZE = 32;

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

	void draw() override;
};
