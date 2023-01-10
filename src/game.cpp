#include "game.hpp"

Game::Game()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		this->enemies[i] = nullptr;
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		this->towers[i] = nullptr;
	this->level = 0;
	this->money = 0;
	this->wave = 0;
}

Game::~Game()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		delete this->enemies[i];
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		delete this->towers[i];
}

void Game::load(std::string seed, Checkpoint* checkpointList, int nbCheckpoint)
{
	this->grid.loadGrid(seed);
	this->grid.loadCheckpoints(checkpointList, nbCheckpoint);
}

void Game::update()
{
	this->mUpdateEnemies();
	this->mUpdateTowers();
}

void Game::draw()
{
	this->grid.draw();
	this->mDrawEnemies();
	this->mDrawTowers();
}

void Game::mUpdateEnemies()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i])
			this->enemies[i]; // TODO add update();
}

void Game::mUpdateTowers()
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i])
			this->towers[i]->update(this->enemies, MAX_NB_ENEMIES); // TODO make it more flexible?
}

void Game::mDrawEnemies()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i])
			this->enemies[i]->draw();
}

void Game::mDrawTowers()
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i])
			this->towers[i]->draw();
}
