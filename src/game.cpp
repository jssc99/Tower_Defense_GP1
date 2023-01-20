#include "game.hpp"

#include "calc.hpp"


Game::Game()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		this->mEnemies[i] = nullptr;
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		this->mTowers[i] = nullptr;
	this->mCastle = nullptr;
	this->mMenu.loadPurchaseMenu(&this->mGrid);
	this->mMenu.setMenu(Type_Menu::MAIN);
}

Game::~Game()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->mEnemies[i])
			delete this->mEnemies[i];
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->mTowers[i])
			delete this->mTowers[i];
	delete this->mCastle;
}

void Game::launchLvl(int lvl)
{
	this->mCurrentLevelId = lvl - 1;
	this->mMoney = 150;
	this->mWave = 0;
	this->mEnemySpawnTimer = 0.f;
	this->mWaveAdvancement = 0;
	this->mWaveCooldown = 0.f;
	this->mTowerPlaced = 0;
	this->mCastle = new Castle;
	this->mGrid.loadGrid(this->lvl[lvl - 1].seed);
	this->mGrid.loadCheckpoints(this->lvl[lvl - 1].checkpointList, this->lvl[lvl - 1].nbCheckpoints, this->mCastle);
	this->mMenu.setMenu(Type_Menu::IN_GAME);
}

void Game::unloadLvl()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->mEnemies[i]) this->mEnemies[i] = nullptr;
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->mTowers[i]) this->mTowers[i] = nullptr;
	this->mCastle = nullptr;
	this->mEnemySpawnTimer = 0.f;
	this->mGrid.unloadGrid();
}

void Game::update()
{
	switch (this->mMenu.update())
	{
	case 1: { // place tower
		Square* s = this->mGrid.getSquare(this->mMenu.getSelection()->pos);
		if ((this->mMoney - this->mMenu.getSelection()->getPrice()) > -1 && s->canPlaceTower())
			this->placeTower(s); }
		  break;
	case 2:// close game
		this->closeGame = true;
		break;

	case 3:// close lvl
		this->unloadLvl();
		this->mMenu.setMenu(Type_Menu::MAIN);
		break;

	case 11:// load lvl 1
		this->launchLvl(1);
		break;

	case 12:// load lvl 2
		this->launchLvl(2);
		break;

	default:
		break;
	}
	if (this->mMenu.getMenu() == Type_Menu::IN_GAME) this->updateInGame();
}

void Game::draw()
{
	this->mGrid.draw();
	if (this->mMenu.getMenu() == Type_Menu::IN_GAME || this->mMenu.getMenu() == Type_Menu::PAUSE) {
		this->drawTowers();
		this->drawEnemies();
		this->drawCastle();
		this->mMenu.draw(this->mCurrentLevelId + 1, this->mWave + 1, this->mMoney, this->mTowerPlaced);
	}
	if (this->mMenu.getMenu() == Type_Menu::IN_GAME)
		this->mCastle->health.draw(L_HEALTH_SIZE * 2, H_HEALTH_SIZE * 2);
	else this->mMenu.draw();
}

void Game::drawDebug()
{
	this->mGrid.drawCheckpoints();
	this->mGrid.drawGrid();
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->mTowers[i] != nullptr && this->mTowers[i]->hasTarget())
			this->mTowers[i]->drawTarget();
}

void Game::addMoney(int m)
{
	this->mMoney += m;
}

void Game::updateInGame()
{
	this->updateEnemies();
	this->updateTowers();
	if (this->mCastle->isDead())
		this->mMenu.setMenu(Type_Menu::LOSE);
	if (this->mWave == this->lvl[this->mCurrentLevelId].nbWaves)
		this->mMenu.setMenu(Type_Menu::VICTORY);
	if ((this->mWaveCooldown += ImGui::GetIO().DeltaTime) >= 10.f)
		this->updateWave();
}

void Game::updateWave()
{
	if ((this->mEnemySpawnTimer += ImGui::GetIO().DeltaTime) >= 3.f) {
		if (!this->lvl[this->mCurrentLevelId].wave[mWave][this->mWaveAdvancement + 1] && this->isWaveDead()) {
			this->mWave++;
			this->mWaveAdvancement = 0;
			this->mWaveCooldown = 0.f;
		}
		else if (this->lvl[this->mCurrentLevelId].wave[mWave][this->mWaveAdvancement + 1])
			this->spawnEnemy((Type_Enemy)(this->lvl[this->mCurrentLevelId].wave[mWave][this->mWaveAdvancement++]));
	}
}

void Game::updateEnemies()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->mEnemies[i] != nullptr) {
			this->mEnemies[i]->update(this->mGrid.getCheckpoints(), this->mGrid.getNbCheckpoints(), this->mCastle, this->gameSpeed, this->mEnemies);
			if (this->mEnemies[i]->isDead()) {
				this->mMoney += this->mEnemies[i]->getLoot();
				this->mEnemies[i] = nullptr;
			}
			else if (this->mEnemies[i]->isAtEndOfPath(this->lvl[this->mCurrentLevelId].nbCheckpoints)) {
				this->mEnemies[i]->update(this->mGrid.getCheckpoints(), this->mGrid.getNbCheckpoints(), this->mCastle, this->gameSpeed, this->mEnemies);
				this->mEnemies[i] = nullptr;
			}
		}
}

void Game::updateTowers()
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->mTowers[i] != nullptr)
			this->mTowers[i]->update(this->mEnemies, MAX_NB_ENEMIES, &this->mMoney, this->gameSpeed);
}

void Game::drawEnemies() const
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->mEnemies[i]) this->mEnemies[i]->draw();
}

void Game::drawTowers() const
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->mTowers[i]) this->mTowers[i]->draw();
}

void Game::drawCastle() const
{
	if (this->mCastle) this->mCastle->draw();
}

bool Game::isWaveDead() const
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->mEnemies[i]) return false;
	return true;
}

void Game::placeTower(Square* s)
{
	int id = this->getFreeTowerSpotId();
	if (!(id < 0)) {
		switch (this->mMenu.getSelection()->getType())
		{
		case Type_Tower::BASIC:
			this->mTowers[id] = new Basic;
			break;
		case Type_Tower::QUICK:
			this->mTowers[id] = new Quick;
			break;
		case Type_Tower::EXPLOSIVE:
			this->mTowers[id] = new Explosive;
			break;
		case Type_Tower::SLOW:
			this->mTowers[id] = new Slow;
			break;
		case Type_Tower::NONE: // shoudn't happen
		default:
			this->mTowers[id] = new Tower;
			break;
		}
		this->mTowers[id]->setPos(s->getPosCenter());
		this->mMoney -= this->mTowers[id]->getPrice();
		this->mTowerPlaced++;
		s->cantHaveTower();
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
			this->mEnemies[id] = new Soldier;
			break;
		case Type_Enemy::KNIGHT:
			this->mEnemies[id] = new Knight;
			break;
		case Type_Enemy::HEALER:
			this->mEnemies[id] = new Healer;
			break;
		case Type_Enemy::NONE: // shoudn't happen
		default:
			this->mEnemies[id] = new Enemy;
			break;
		}
		this->mEnemies[id]->spawn(this->mGrid.getSpawnPoint());
		this->mEnemySpawnTimer = 0.f;
	}
}

// returns -1 if no spot found
int Game::getFreeEnemySpotId() const
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (!this->mEnemies[i] || this->mEnemies[i] == nullptr)
			return i;
	return -1;
}

// returns -1 if no spot found
int Game::getFreeTowerSpotId() const
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (!this->mTowers[i] || this->mTowers[i] == nullptr)
			return i;
	return -1;
}