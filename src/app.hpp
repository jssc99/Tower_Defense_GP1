#pragma once

#include "game.hpp"

class App
{
public:
	Game game;

	bool closeApp = false;

	App();
	~App();

	void Update();

private:
	bool mDebugMenu = false;
	bool mDrawDebug = false;
};