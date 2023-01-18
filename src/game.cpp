#include "game.hpp"

#include "calc.hpp"

Game::Game()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		this->enemies[i] = nullptr;
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		this->towers[i] = nullptr;
	this->castle = nullptr;
	this->menu.loadPurchaseMenu(&this->grid);
	this->menu.setMenu(Type_Menu::MAIN);
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

void Game::launchLvl(int lvl)
{
	this->mCurrentLevelId = lvl - 1;
	this->mMoney = 150;
	this->mWave = 0;
	this->mEnemySpawnTimer = 0.f;
	this->mWaveAdvancement = 0;
	this->mWaveCooldown = 0.f;
	this->mTowerPlaced = 0;
	this->mEnemiesAlive = 0;
	this->castle = new Castle;
	this->grid.loadGrid(this->lvl[lvl - 1].seed);
	this->grid.loadCheckpoints(this->lvl[lvl - 1].checkpointList, this->lvl[lvl - 1].nbCheckpoints, this->castle);
	this->menu.setMenu(Type_Menu::IN_GAME);
}

void Game::unloadLvl()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i]) this->enemies[i] = nullptr;
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i]) this->towers[i] = nullptr;
	this->castle = nullptr;
	this->mEnemySpawnTimer = 0.f;
	this->grid.unloadGrid();
}

void Game::update()
{
	switch (this->menu.update())
	{
	case 1: { // place tower
		Square* s = this->grid.getSquare(this->menu.purchaseMenu.selection.pos);
		if ((this->mMoney - this->menu.purchaseMenu.selection.price) > -1 && s->canPlaceTower())
			this->placeTower(s); }
		  break;
	case 2:// close game
		this->closeGame = true;
		break;

	case 3:// close lvl
		this->unloadLvl();
		this->menu.setMenu(Type_Menu::MAIN);
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
	if (this->menu.getMenu() == Type_Menu::IN_GAME) this->updateInGame();
}

void Game::draw()
{
	this->grid.draw();
	if (this->menu.getMenu() == Type_Menu::IN_GAME || this->menu.getMenu() == Type_Menu::PAUSE) {
		this->drawTowers();
		this->drawEnemies();
		this->menu.draw(this->mCurrentLevelId + 1, this->mWave + 1, this->mMoney, this->mTowerPlaced);
	}
	if (this->menu.getMenu() == Type_Menu::IN_GAME)
		this->castle->health.draw(L_HEALTH_SIZE * 2, H_HEALTH_SIZE * 2);
	else this->menu.draw();
}

void Game::drawDebug()
{
	this->grid.drawCheckpoints();
	this->grid.drawGrid();
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i] != nullptr && this->towers[i]->current_target != nullptr)
			this->towers[i]->drawTarget();
}

void Game::addMoney(int m)
{
	this->mMoney += m;
}

void Game::updateInGame()
{
	this->updateEnemies();
	this->updateTowers();
	if (this->castle->isDead())
		this->menu.setMenu(Type_Menu::LOSE);
	if (this->mWave == this->lvl[this->mCurrentLevelId].nbWaves)
		this->menu.setMenu(Type_Menu::VICTORY);
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
		if (this->enemies[i] != nullptr) {
			this->enemies[i]->update(this->grid.checkpoints, this->grid.getNbCheckpoints(), this->castle, this->mGameSpeed, this->enemies);
			if (this->enemies[i]->isDead()) {
				this->mMoney += this->enemies[i]->loot;
				this->enemies[i] = nullptr;
				this->mEnemiesAlive--;
			}
			else if (this->enemies[i]->checkId - 1 == this->lvl[this->mCurrentLevelId].nbCheckpoints) {
				this->enemies[i]->update(this->grid.checkpoints, this->grid.getNbCheckpoints(), this->castle, this->mGameSpeed, this->enemies);
				this->enemies[i] = nullptr;
				this->mEnemiesAlive--;
			}
		}
}

void Game::updateTowers()
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i] != nullptr)
			this->towers[i]->update(this->enemies, this->mEnemiesAlive, &this->mMoney, this->mGameSpeed);
}

void Game::drawEnemies() const
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i]) this->enemies[i]->draw();
}

void Game::drawTowers() const
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i]) this->towers[i]->draw();
}

bool Game::isWaveDead() const
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i]) return false;
	return true;
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
		this->mMoney -= this->towers[id]->price;
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
		this->mEnemySpawnTimer = 0.f;
		this->mEnemiesAlive++;
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