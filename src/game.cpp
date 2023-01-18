﻿#include "game.hpp"

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
	this->castle->health.posCenter = CASTLE_LIFE_POS;
	this->grid.loadGrid(this->lvl[(lvl - 1)].seed);
	this->grid.loadCheckpoints(this->lvl[(lvl - 1)].checkpointList, this->lvl[(lvl - 1)].nbCheckpoints, this->castle);
	//this->grid.makePathLookGood();
	this->money = 100;
	this->wave = 0;
	this->enSpwTimer = 0.f;
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
	this->enSpwTimer = 0.f;
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

	case 3:// close lvl
		this->unloadLvl();
		this->menu.load(Type_Menu::MAIN);
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
	if (this->menu.menu == Type_Menu::IN_GAME) {
		this->updateEnemies();
		this->updateTowers();
		if (this->castle->isDead())
			this->menu.menu = Type_Menu::LOSE;
		if (0/*win contition TODO*/)
			this->menu.menu = Type_Menu::VICTORY;
	}
}

void Game::draw()
{
	this->grid.draw();
	if (this->menu.menu == Type_Menu::IN_GAME || this->menu.menu == Type_Menu::PAUSE) {
		this->drawTowers();
		this->drawEnemies();
		this->menu.draw(this->mCurrentLevelId + 1, this->wave, this->money, this->towerPlaced); 
	}
	if (this->menu.menu == Type_Menu::IN_GAME)
		this->castle->health.draw();
	else this->menu.draw();
}

void Game::drawDebug()
{
	this->grid.drawCheckpoints();
	this->grid.drawGrid();
}

void Game::updateEnemies()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i] != nullptr) {
			this->enemies[i]->update(this->grid.chkpList, this->grid.nbCheckpoints, this->castle);
			if (this->enemies[i]->isDead()) {
				this->money += this->enemies[i]->loot;
				this->enemies[i] = nullptr;
			}
		}
}

void Game::updateTowers()
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i] != nullptr)
			this->towers[i]->update(this->enemies, MAX_NB_ENEMIES, &this->money);
}

void Game::drawEnemies() const
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i]) 
			this->enemies[i]->draw();
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
	if (!(id < 0)) {
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
		this->towerPlaced++;
	}
}

void Game::spawnEnemy(Type_Enemy type)
{
	int id = this->getFreeEnemySpotId();
	if (!(id < 0))
	{
		switch (type)
		{
		case Type_Enemy::SOLDIER:
			this->enemies[id] = new Soldier;
			break;
		case Type_Enemy::KNIGHT:
			this->enemies[id] = new Knight;
			break;
		case Type_Enemy::HEALER:
			this->enemies[id] = new Healer;
			break;
		case Type_Enemy::NONE: // shoudn't happen
		default:
			this->enemies[id] = new Enemy;
			break;
		}
		this->enemies[id]->spawn(this->grid.getSpawnPoint());
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
