#pragma once

#include "entities/enemy.hpp"
#include "calc.hpp"
#include "grid.hpp"
#include "entities/towers/basic_tower.hpp"
#include "entities/towers/explosive_tower.hpp"
#include "entities/towers/quick_tower.hpp"
#include "entities/towers/slow_tower.hpp"

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 704;

class App
{
public:
	Grid grid;
	Tower *towers[50];
	Enemy *enemies[10];

	App();
	~App();

	void Update();
};