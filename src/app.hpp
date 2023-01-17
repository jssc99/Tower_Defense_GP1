#pragma once

#include "game.hpp"

class App
{
public:
	Game game;
	bool debug = false;
	bool closeApp = false;

	App();
	~App();

	void Update();
};