#include "square.hpp"

#include "../calc.hpp"

Square::Square()
{
	this->mType = Type_Square::NONE;
	this->loadTexture("assets/towerDefense_tile015.png");
	if (this->mHasDecor)
		this->mDecor = ImGuiUtils::LoadTexture("assets/towerDefense_tile015.png");
}

Square::~Square()
{
	this->unloadTexture();
}

void Square::setType(Type_Square type)
{
	this->mType = type;
	int randomChoice = (rand() % 40);
	switch (type)
	{
	case Type_Square::NONE:
		this->loadTexture("assets/towerDefense_tile015.png");
		ImGuiUtils::UnloadTexture(this->mDecor);
		this->mHasDecor = false;
		break;
	case Type_Square::BACKGROUND:
		this->loadTexture("assets/towerDefense_tile103.png");
		this->mHasDecor = true;
		if (randomChoice == 10)
			this->mDecor = ImGuiUtils::LoadTexture("assets/towerDefense_tile135.png");
		else if (randomChoice == 20)
			this->mDecor = ImGuiUtils::LoadTexture("assets/towerDefense_tile136.png");
		else if (randomChoice == 30)
			this->mDecor = ImGuiUtils::LoadTexture("assets/towerDefense_tile137.png");
		else this->mHasDecor = false;
		break;
	case Type_Square::GRASS:
		this->mCanHaveTower = true;
		randomChoice /= 10;
		if (randomChoice == 0)
			this->loadTexture("assets/towerDefense_tile024.png");
		else if (randomChoice == 1)
			this->loadTexture("assets/towerDefense_tile157.png");
		else if (randomChoice == 2)
			this->loadTexture("assets/towerDefense_tile162.png");
		else if (randomChoice == 3)
			this->loadTexture("assets/towerDefense_tile231.png");
		break;
	case Type_Square::PATH:
		this->loadTexture("assets/towerDefense_tile158.png");
		//this->loadTexture("assets/towerDefense_tile060.png"); // if makePathLookGood() is finisheds
		break;
	case Type_Square::CASTLE:
		this->loadTexture("assets/towerDefense_tile090.png");
		break;
	case Type_Square::SPAWN:
		this->loadTexture("assets/towerDefense_tile068.png");
		break;
	default:
		break;
	}
}

Type_Square Square::getType()
{
	return this->mType;
}

float2 Square::getPosCenter() const
{
	return this->pos + H_SQUARE_SIZE;
}

bool Square::canPlaceTower() const
{
	if (this->mType == Type_Square::GRASS && this->mCanHaveTower)
		return true;
	else
		return false;
}

void Square::cantHaveTower()
{
	this->mCanHaveTower = false;
}

void Square::draw()
{
	ImGuiUtils::DrawTextureEx(*ImGui::GetBackgroundDrawList(), this->sprite, this->getPosCenter(), { 0.5f,0.5f });
	if (this->mHasDecor)
		ImGuiUtils::DrawTextureEx(*ImGui::GetBackgroundDrawList(), this->mDecor, this->getPosCenter(), { 0.5f,0.5f });
}

void Square::drawPos()
{
	char temp[10];
	sprintf(temp, "%d", (int)(this->pos.y / SQUARE_SIZE));
	ImGui::GetBackgroundDrawList()->AddText(this->pos, WHITE, temp);
	sprintf(temp, "%d", (int)(this->pos.x / SQUARE_SIZE));
	ImGui::GetBackgroundDrawList()->AddText(this->getPosCenter(), WHITE, temp);
}