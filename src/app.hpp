#pragma once

#include "game.hpp"

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 704;

class App
{
public:
	bool debug;
	Game game;

	App();
	~App();

	void Update();
};