#pragma once

#include "game.hpp"

class App
{
public:
	Game game;
	bool debug;

	App();
	~App();

	void Update();
};