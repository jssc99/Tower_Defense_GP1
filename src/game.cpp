#include "game.hpp"

#include "calc.hpp"

Game::Game()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		this->enemies[i] = nullptr;
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		this->towers[i] = nullptr;
	this->money = 0;
	this->wave = 0;
	this->menu.loadPurchaseMenu(&this->grid);
	this->menu.load(Type_Menu::LOADING);
}

Game::~Game()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i])
			delete this->enemies[i];
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i])
			delete this->towers[i];
}

void Game::loadLvl(int lvl)
{
	this->grid.loadGrid(this->lvl[(lvl - 1)].seed);
	this->grid.loadCheckpoints(this->lvl[(lvl - 1)].checkpointList, this->lvl[(lvl - 1)].nbCheckpoints);
	this->grid.makePathLookGood();
	this->money = 100;
	this->wave = 0;
	this->menu.load(Type_Menu::IN_GAME);
}

void Game::update()
{
	if (this->menu.update())
	{
		Square* s = this->grid.getSquare(this->menu.purchaseMenu.selection.pos);
		if ((this->money - this->menu.purchaseMenu.selection.price) > -1 && s->canPlaceTower())
			this->placeTower(s);
	}
	this->updateEnemies();
	//enemies dead ? TODO
	this->updateTowers();
}

void Game::draw()
{
	this->grid.draw();
	this->drawTowers();
	this->drawEnemies();
	this->menu.draw(&this->grid);
	this->drawCastle();
	this->drawMenu();
}

void Game::drawDebug()
{
	this->grid.drawCheckpoints();
	this->grid.drawGrid();
}

void Game::updateEnemies()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i])
			this->enemies[i]->update(this->grid.chkpList, this->grid.nbCheckpoints, &this->castle);
}

void Game::updateTowers()
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i])
			this->towers[i]->update(this->enemies, MAX_NB_ENEMIES);
}

void Game::drawEnemies()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i])
			this->enemies[i]->draw();
}

void Game::drawTowers()
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i])
			this->towers[i]->draw();
}

void Game::placeTower(Square* s)
void Game::drawCastle()
{
	int id = this->getFreeTowerSpotId();
	if (id != -1) {
		switch (this->menu.purchaseMenu.selection.type)
	this->castle.drawHealth();
}

void Game::drawMenu()// SQ : 20 16 to SQ : 21 23
		{
		case Type_Tower::BASIC:
			this->towers[id] = new Basic;
			break;
		case Type_Tower::QUICK:
			this->towers[id] = new Quick;
			break;
		case Type_Tower::EXPLOSIVE:
			this->towers[id] = new Explosive;
			break;
		case Type_Tower::SLOW:
			this->towers[id] = new Slow;
			break;
		case Type_Tower::NONE: // shoudn't happen
		default:
			this->towers[id] = new Tower;
			break;
		}
		this->towers[id]->setPos(s->getPosCenter());
		this->money -= this->towers[id]->price;
		s->canHaveTower = false;
	}
}

// returns -1 if no spot found
int Game::getFreeEnemySpotId()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (!this->enemies[i] || this->enemies[i] == nullptr)
			return i;
	return -1;
}

// returns -1 if no spot found
int Game::getFreeTowerSpotId()
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (!this->towers[i] || this->towers[i] == nullptr)
			return i;
	return -1;
}