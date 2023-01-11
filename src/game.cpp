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

	// menu is hard placed
	{
		this->purchaseMenu.tow[0] = new Basic;
		this->purchaseMenu.tow[1] = new Quick;
		this->purchaseMenu.tow[2] = new Slow;
		this->purchaseMenu.tow[3] = new Explosive;
		this->purchaseMenu.tow[0]->pos = { this->grid.square[20][16].pos.x + H_SQUARE_SIZE, this->grid.square[20][16].pos.y + H_SQUARE_SIZE };
		this->purchaseMenu.tow[1]->pos = { this->grid.square[20][18].pos.x + H_SQUARE_SIZE, this->grid.square[20][18].pos.y + H_SQUARE_SIZE };
		this->purchaseMenu.tow[2]->pos = { this->grid.square[20][20].pos.x + H_SQUARE_SIZE, this->grid.square[20][20].pos.y + H_SQUARE_SIZE };
		this->purchaseMenu.tow[3]->pos = { this->grid.square[20][22].pos.x + H_SQUARE_SIZE, this->grid.square[20][22].pos.y + H_SQUARE_SIZE };
	}
}

Game::~Game()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (this->enemies[i])
			delete this->enemies[i];
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (this->towers[i])
			delete this->towers[i];
	for (int i = 0; i < 4; i++)
		if (this->purchaseMenu.tow[i])
			delete this->purchaseMenu.tow[i];
}

void Game::load(std::string seed, Checkpoint* checkpointList, int nbCheckpoint)
{
	this->grid.loadGrid(seed);
	this->grid.loadCheckpoints(checkpointList, nbCheckpoint);
}

void Game::update()
{
	this->mUpdateMenu();
	this->mUpdateEnemies();
	this->mUpdateTowers();
}

void Game::draw()
{
	this->grid.draw();
	this->mDrawMenu();
	this->mDrawTowers();
	this->mDrawEnemies();
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
			this->towers[i]->update(this->enemies, MAX_NB_ENEMIES);
}

void Game::mUpdateMenu()
{
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

void Game::mDrawMenu()// SQ : 20 16 to SQ : 21 23
{
	ImDrawList* fgDrawlist = ImGui::GetBackgroundDrawList();
	fgDrawlist->AddRectFilled({ this->grid.square[20][16].pos.x, this->grid.square[20][16].pos.y },
		{ this->grid.square[21][23].pos.x + SQUARE_SIZE, this->grid.square[21][23].pos.y + SQUARE_SIZE },
		WHITE, 5.f);
	for (int i = 0; i < 4; i++) {
		this->purchaseMenu.tow[i]->draw(0);
		fgDrawlist->AddText({ this->grid.square[21][16 + 2 * i].pos.x, this->grid.square[21][16 + 2 * i].pos.y }, BLACK, this->purchaseMenu.tow[i]->getType());
		char price[20];
		sprintf(price, "%d c", this->purchaseMenu.tow[i]->price);
		fgDrawlist->AddText({ this->grid.square[21][16 + 2 * i].pos.x + 1.f, this->grid.square[21][16 + 2 * i].pos.y + H_SQUARE_SIZE }, BLACK, price);
	}
}