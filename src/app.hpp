#pragma once

#include "entities/enemy.hpp"
#include "calc.hpp"
#include "grid.hpp"

class App
{
public:
	Grid grid;
	Enemy e;

	App();
	~App();

	void Update();
};