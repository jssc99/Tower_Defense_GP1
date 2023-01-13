#include "game.hpp"

#include "calc.hpp"

#define M this->purchaseMenu

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
		M.tow[0] = new Basic;
		M.tow[1] = new Quick;
		M.tow[2] = new Slow;
		M.tow[3] = new Explosive;
		for (int i = 0; i < 4; i++)
			M.tow[i]->pos = { this->grid.square[20][16 + 2 * i].pos.x + H_SQUARE_SIZE, this->grid.square[20][16 + 2 * i].pos.y + H_SQUARE_SIZE };
		M.hasSelected = false;
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
		if (M.tow[i])
			delete M.tow[i];
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
	this->mDrawTowers();
	this->mDrawEnemies();
	this->mDrawMenu();
}

void Game::drawDebug()
{
	this->grid.drawCheckpoints();
	this->grid.drawGrid();
}

bool Game::canPlaceTower(Tower t, Square* s)
{
	if (s->type == Type::GRASS)
		for (int i = 0; i < MAX_NB_TOWERS; i++)
			if (this->towers[i] &&
				this->towers[i]->pos != (s->pos + (float)H_SQUARE_SIZE))
				return true;
	return false;
}

void Game::placeTower(float2 posCenter)
{
	Square* s = this->grid.getSquare(posCenter);
	s->canHaveTower = false;
	//this->getFreeTowerSpot() = new (this->purchaseMenu.selection);
}

void Game::placeTower(float xCenter, float yCenter)
{
	this->placeTower({ xCenter,yCenter });
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
	ImVec2 mouse = ImGui::GetMousePos();
	if (!M.hasSelected && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		for (int i = 0; i < 4; i++)
			if (M.hasSelected == false &&
				(M.tow[i]->pos.x - (float)H_TOWER_SIZE <= mouse.x && mouse.x <= M.tow[i]->pos.x + (float)H_TOWER_SIZE) &&
				(M.tow[i]->pos.y - (float)H_TOWER_SIZE <= mouse.y && mouse.y <= M.tow[i]->pos.y + (float)H_TOWER_SIZE)) {
				M.selection = *M.tow[i];
				M.hasSelected = true;
			}
	if (M.hasSelected && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
		M.selection.setPos(mouse.x, mouse.y);
	if (M.hasSelected && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
		M.hasSelected = false;
		if (this->canPlaceTower(M.selection, this->grid.getSquare(M.selection.pos))) // TODO
			printf("place\n");
	}
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
	ImDrawList* bgDrawlist = ImGui::GetBackgroundDrawList();
	bgDrawlist->AddRectFilled({ this->grid.square[20][16].pos.x, this->grid.square[20][16].pos.y },
		{ this->grid.square[21][23].pos.x + SQUARE_SIZE, this->grid.square[21][23].pos.y + SQUARE_SIZE },
		WHITE, 5.f);
	for (int i = 0; i < 4; i++) {
		M.tow[i]->draw(0);
		bgDrawlist->AddText({ this->grid.square[21][16 + 2 * i].pos.x, this->grid.square[21][16 + 2 * i].pos.y }, BLACK, M.tow[i]->getType());
		char price[20];
		sprintf(price, "-%d c", M.tow[i]->price);
		bgDrawlist->AddText({ this->grid.square[21][16 + 2 * i].pos.x, this->grid.square[21][16 + 2 * i].pos.y + H_SQUARE_SIZE }, BLACK, price);
	}
	if (M.hasSelected)
		M.selection.draw();
}

Enemy* Game::getFreeEnemySpot()
{
	for (int i = 0; i < MAX_NB_ENEMIES; i++)
		if (!this->enemies[i])
			return this->enemies[i];
	return nullptr;
}

Tower* Game::getFreeTowerSpot()
{
	for (int i = 0; i < MAX_NB_TOWERS; i++)
		if (!this->towers[i])
			return this->towers[i];
	return nullptr;
}
