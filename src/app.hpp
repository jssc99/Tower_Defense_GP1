#pragma once

#include "game.hpp"

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 704;

class App
{
public:
	Game game;
	bool debug;

	App();
	~App();

	void Update();
};