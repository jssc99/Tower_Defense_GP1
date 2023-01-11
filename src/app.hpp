#pragma once

#include "entities/enemy.hpp"
#include "entities/castle.hpp"
#include "calc.hpp"
#include "grid.hpp"

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 704;

class App
{
public:
	Grid grid;
	Enemy e;
	Castle c;

	App();
	~App();

	void Update();
};