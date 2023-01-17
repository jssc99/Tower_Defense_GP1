#include "game.hpp"

#include "calc.hpp"

Game::Game()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		this->enemies[i] = nullptr;
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		this->towers[i] = nullptr;
	this->menu.loadPurchaseMenu(&this->grid);
	this->menu.load(Type_Menu::MAIN);
}

Game::~Game()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i])
			delete this->enemies[i];
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i])
			delete this->towers[i];
	delete this->castle;
}

void Game::loadLvl(int lvl)
{
	this->mCurrentLevelId = lvl - 1;
	this->castle = new Castle;
	this->grid.loadGrid(this->lvl[(lvl - 1)].seed);
	this->grid.loadCheckpoints(this->lvl[(lvl - 1)].checkpointList, this->lvl[(lvl - 1)].nbCheckpoints, this->castle);
	this->grid.makePathLookGood();
	this->money = 100;
	this->wave = 0;
	this->menu.load(Type_Menu::IN_GAME);
}

void Game::unloadLvl()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i])
			this->enemies[i] = nullptr;
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i])
			this->towers[i] = nullptr;
	this->castle = nullptr;
	this->grid.unloadGrid();
}

void Game::update()
{
	switch (this->menu.update())
	{
	case 1: {
		Square* s = this->grid.getSquare(this->menu.purchaseMenu.selection.pos);
		if ((this->money - this->menu.purchaseMenu.selection.price) > -1 && s->canPlaceTower())
			this->placeTower(s); }
		  break;
	case 2:// close game
		this->closeGame = true;
		break;

	case 11:// load lvl 1
		this->loadLvl(1);
		break;

	case 12:// load lvl 2
		this->loadLvl(2);
		break;
	
	default:
		break;
	}
	this->updateEnemies();
	this->updateTowers();
}

void Game::draw()
{
	this->grid.draw();
	this->drawTowers();
	this->drawEnemies();
	this->menu.draw(this->mCurrentLevelId + 1, this->wave, this->money);
	if (this->castle) this->castle->drawHealth();
}

void Game::drawDebug()
{
	this->grid.drawCheckpoints();
	this->grid.drawGrid();
}

void Game::updateEnemies()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i] || this->enemies[i] != nullptr) {
			this->enemies[i]->update(this->grid.chkpList, this->grid.nbCheckpoints, this->castle);
			if (this->enemies[i]->healthSystem.health <= 0)
				this->enemies[i] = nullptr;
		}
}

void Game::updateTowers()
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i] || this->towers[i] != nullptr)
			this->towers[i]->update(this->enemies, MAX_NB_ENEMIES);
}

void Game::drawEnemies() const
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i]) {
			this->enemies[i]->draw();
			this->enemies[i]->drawHealth();
		}
}

void Game::drawTowers() const
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i])
			this->towers[i]->draw();
}

void Game::placeTower(Square* s)
{
	int id = this->getFreeTowerSpotId();
	if (id != -1) {
		switch (this->menu.purchaseMenu.selection.type)
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
int Game::getFreeEnemySpotId() const
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (!this->enemies[i] || this->enemies[i] == nullptr)
			return i;
	return -1;
}

// returns -1 if no spot found
int Game::getFreeTowerSpotId() const
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (!this->towers[i] || this->towers[i] == nullptr)
			return i;
	return -1;
}
