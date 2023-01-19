#include "grid.hpp"

#include "calc.hpp"

Grid::Grid()
{
	for (int i = 0; i < MAX_NB_CHECKPOINTS; i++)
		this->mCheckpoints[i] = { 0, STOP, STOP };
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			this->mSquares[i][j].pos = { (float)j * SQUARE_SIZE, (float)i * SQUARE_SIZE };
}

void Grid::loadGrid(std::string seed)
{
	int id = 0;
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			if (seed[id])
				this->mSquares[i][j].setType((Type_Square)seed[id++]);
			else id++;
	// this->makePathLookGood();
}

void Grid::unloadGrid()
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			this->mSquares[i][j].setType(Type_Square::NONE);
	this->mNbCheckpoints = 0;
	this->mSpawnPoint = STOP;
}

void Grid::loadCheckpoints(const Checkpoint* checkpointList, int nbCheckpoints, Castle* castle)
{
	this->mNbCheckpoints = nbCheckpoints;
	for (int i = 0; i < nbCheckpoints; i++) {
		this->mCheckpoints[i] = checkpointList[i];
		if (i + 1 == nbCheckpoints)
			castle->pos = this->getSquare(checkpointList[i].pos)->pos; // useless ? TODO
		this->mCheckpoints[i].pos = this->getSquareXY((int)checkpointList[i].pos.x, (int)checkpointList[i].pos.y)->pos;
		this->mCheckpoints[i].pos.y += SQUARE_SIZE;
	}
}

void Grid::draw()
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			this->mSquares[i][j].draw();
}

void Grid::drawGrid()
{
	ImDrawList* bgDrawList = ImGui::GetBackgroundDrawList();
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++) {
			auto x = (float)(j * SQUARE_SIZE);
			auto y = (float)(i * SQUARE_SIZE);
			auto z = (float)(NB_SQUARES_ROW * SQUARE_SIZE);
			bgDrawList->AddLine({ x,y }, { x,y + z }, BLACK, 0.5f);
			bgDrawList->AddLine({ x,y }, { x + z,y }, BLACK, 0.5f);
			this->mSquares[i][j].drawPos();
		}
}

// for debug purpose
void Grid::drawCheckpoints()
{
	for (int i = 0; i < this->mNbCheckpoints; i++)
		this->mCheckpoints[i].draw();
}

int Grid::getNbCheckpoints() const
{
	return this->mNbCheckpoints;
}

Checkpoint* Grid::getCheckpoints()
{
	return this->mCheckpoints;
}

float2 Grid::getSpawnPoint()
{
	if (this->mSpawnPoint == STOP) {
		for (int i = 0; i < NB_SQUARES_ROW; i++)
			for (int j = 0; j < NB_SQUARES_COL; j++)
				if (this->mSquares[i][j].getType() == Type_Square::SPAWN)
					this->mSpawnPoint = { this->mSquares[i][j].pos.x,this->mSquares[i][j].pos.y + SQUARE_SIZE };
	}
	return this->mSpawnPoint;
}

// Serves different function than getSquareXY(float2 XY)
Square* Grid::getSquare(float2 point)
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			if ((this->mSquares[i][j].pos.x <= point.x && point.x <= this->mSquares[i][j].pos.x + (float)SQUARE_SIZE) &&
				(this->mSquares[i][j].pos.y <= point.y && point.y <= this->mSquares[i][j].pos.y + (float)SQUARE_SIZE))
				return &this->mSquares[i][j];
	return nullptr;
}

// Serves different function than getSquare(float2 point)
Square* Grid::getSquareXY(int x, int y)
{
	if (&this->mSquares[x][y])
		return &this->mSquares[x][y];
	return nullptr;
}

void Grid::makePathLookGood() // TODO, maybe
{
	int id = 0;
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++) {
			if (this->mSquares[i][j].getType() == Type_Square::SPAWN)
				this->mSquares[i][j].loadTexture("assets/towerDefense_tile047.png");
			else if (this->mSquares[i][j].getType() == Type_Square::PATH) {
				if (this->mSquares[(i + 1) % NB_SQUARES_ROW][j].getType() == Type_Square::GRASS) { // DOWN IS GRASS
					if (this->mSquares[i][(j + 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // DOWN & RIGHT IS GRASS
						this->mSquares[i][j].loadTexture("assets/towerDefense_tile027.png");
					else if (this->mSquares[i][(j - 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // DOWN & LEFT IS GRASS
						this->mSquares[i][j].loadTexture("assets/towerDefense_tile026.png");
					else this->mSquares[i][j].loadTexture("assets/towerDefense_tile001.png");
				}
				else if (this->mSquares[(i - 1) % NB_SQUARES_ROW][j].getType() == Type_Square::GRASS) { // UP IS GRASS
					if (this->mSquares[i][(j + 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // UP & RIGHT IS GRASS
						this->mSquares[i][j].loadTexture("assets/towerDefense_tile004.png");
					else if (this->mSquares[i][(j - 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // UP & LEFT IS GRASS
						this->mSquares[i][j].loadTexture("assets/towerDefense_tile003.png");
					else this->mSquares[i][j].loadTexture("assets/towerDefense_tile047.png");
				}
				else if (this->mSquares[i][(j + 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // RIGHT IS GRASS
					this->mSquares[i][j].loadTexture("assets/towerDefense_tile023.png");
				else if (this->mSquares[i][(j - 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // LEFT IS GRASS
					this->mSquares[i][j].loadTexture("assets/towerDefense_tile025.png");
			}
		}
}