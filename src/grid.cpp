#include "grid.hpp"

#include "calc.hpp"

Grid::Grid()
{
	for (int i = 0; i < MAX_NB_CHECKPOINTS; i++)
		this->checkpoints[i] = { 0, STOP, STOP };
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			this->squares[i][j].pos = { (float)j * SQUARE_SIZE, (float)i * SQUARE_SIZE };
}

void Grid::loadGrid(std::string seed)
{
	int id = 0;
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			if (seed[id])
				this->squares[i][j].setType((Type_Square)seed[id++]);
			else id++;
	// this->makePathLookGood();
}

void Grid::unloadGrid()
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			this->squares[i][j].setType(Type_Square::NONE);
	this->nNbCheckpoints = 0;
	this->mSpawnPoint = STOP;
}

void Grid::loadCheckpoints(const Checkpoint* checkpointList, int nbCheckpoints, Castle* castle)
{
	this->nNbCheckpoints = nbCheckpoints;
	for (int i = 0; i < nbCheckpoints; i++) {
		this->checkpoints[i] = checkpointList[i];
		if (i + 1 == nbCheckpoints)
			castle->pos = this->getSquare(checkpointList[i].pos)->pos; // useless ? TODO
		this->checkpoints[i].pos = this->getSquareXY(checkpointList[i].pos)->pos;
		this->checkpoints[i].pos.y += SQUARE_SIZE;
	}
}

void Grid::draw()
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			this->squares[i][j].draw();
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
			this->squares[i][j].drawPos();
		}
}

// for debug purpose
void Grid::drawCheckpoints()
{
	for (int i = 0; i < this->nNbCheckpoints; i++)
		this->checkpoints[i].draw();
}

int Grid::getNbCheckpoints() const
{
	return this->nNbCheckpoints;
}

float2 Grid::getSpawnPoint()
{
	if (this->mSpawnPoint == STOP) {
		for (int i = 0; i < NB_SQUARES_ROW; i++)
			for (int j = 0; j < NB_SQUARES_COL; j++)
				if (this->squares[i][j].getType() == Type_Square::SPAWN)
					this->mSpawnPoint = { this->squares[i][j].pos.x,this->squares[i][j].pos.y + SQUARE_SIZE };
	}
	return this->mSpawnPoint;
}

// Serves different function than getSquareXY(float2 XY)
Square* Grid::getSquare(float2 point)
{
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++)
			if ((this->squares[i][j].pos.x <= point.x && point.x <= this->squares[i][j].pos.x + (float)SQUARE_SIZE) &&
				(this->squares[i][j].pos.y <= point.y && point.y <= this->squares[i][j].pos.y + (float)SQUARE_SIZE))
				return &this->squares[i][j];
	return nullptr;
}

// Serves different function than getSquare(float2 point)
Square* Grid::getSquareXY(float2 XY)
{
	if (&this->squares[(int)XY.x][(int)XY.y])
		return &this->squares[(int)XY.x][(int)XY.y];
	return nullptr;
}

void Grid::makePathLookGood() // TODO, maybe
{
	int id = 0;
	for (int i = 0; i < NB_SQUARES_ROW; i++)
		for (int j = 0; j < NB_SQUARES_COL; j++) {
			if (this->squares[i][j].getType() == Type_Square::SPAWN)
				this->squares[i][j].loadTexture("assets/towerDefense_tile047.png");
			else if (this->squares[i][j].getType() == Type_Square::PATH) {
				if (this->squares[(i + 1) % NB_SQUARES_ROW][j].getType() == Type_Square::GRASS) { // DOWN IS GRASS
					if (this->squares[i][(j + 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // DOWN & RIGHT IS GRASS
						this->squares[i][j].loadTexture("assets/towerDefense_tile027.png");
					else if (this->squares[i][(j - 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // DOWN & LEFT IS GRASS
						this->squares[i][j].loadTexture("assets/towerDefense_tile026.png");
					else this->squares[i][j].loadTexture("assets/towerDefense_tile001.png");
				}
				else if (this->squares[(i - 1) % NB_SQUARES_ROW][j].getType() == Type_Square::GRASS) { // UP IS GRASS
					if (this->squares[i][(j + 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // UP & RIGHT IS GRASS
						this->squares[i][j].loadTexture("assets/towerDefense_tile004.png");
					else if (this->squares[i][(j - 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // UP & LEFT IS GRASS
						this->squares[i][j].loadTexture("assets/towerDefense_tile003.png");
					else this->squares[i][j].loadTexture("assets/towerDefense_tile047.png");
				}
				else if (this->squares[i][(j + 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // RIGHT IS GRASS
					this->squares[i][j].loadTexture("assets/towerDefense_tile023.png");
				else if (this->squares[i][(j - 1) % NB_SQUARES_COL].getType() == Type_Square::GRASS) // LEFT IS GRASS
					this->squares[i][j].loadTexture("assets/towerDefense_tile025.png");
			}
		}
}