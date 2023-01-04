#pragma once

#include "entity.hpp"

class Castle : public Entity
{
public:
	int hp;

	Castle() virtual {};
	~Castle() virtual {};

	void updateCastle() virtual {};
};