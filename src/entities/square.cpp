#include "square.hpp"
#include "../calc.hpp"

Square::Square()
{
	this->type = Type_Square::NONE;
	this->loadTexture("assets/towerDefense_tile015.png");
	if ( hasDecor )
		this->decor = ImGuiUtils::LoadTexture("assets/towerDefense_tile015.png");
}

Square::~Square()
{
	this->unloadTexture();
}

void Square::setType(Type_Square type)
{
	this->type = type;
	int randomChoice = (rand() % 40);
	switch (type)
	{
	case Type_Square::NONE:
		this->loadTexture("assets/towerDefense_tile015.png");
		ImGuiUtils::UnloadTexture(this->decor);
		this->hasDecor = false;
		break;
	case Type_Square::BACKGROUND:
		this->loadTexture("assets/towerDefense_tile103.png");
		this->hasDecor = true;
		if (randomChoice == 10)
			this->decor = ImGuiUtils::LoadTexture("assets/towerDefense_tile135.png");
		else if (randomChoice == 20)
			this->decor = ImGuiUtils::LoadTexture("assets/towerDefense_tile136.png");
		else if (randomChoice == 30)
			this->decor = ImGuiUtils::LoadTexture("assets/towerDefense_tile137.png");
		else this->hasDecor = false;
		break;
	case Type_Square::GRASS:
		this->canHaveTower = true;
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

float2 Square::getPosCenter() const
{
	return this->pos + H_SQUARE_SIZE;
}

bool Square::canPlaceTower() const
{
	if (this->type == Type_Square::GRASS && this->canHaveTower)
		return true;
	else
		return false;
}

void Square::draw()
{
	ImGuiUtils::DrawTextureEx(*ImGui::GetBackgroundDrawList(), this->sprite, this->pos + H_SQUARE_SIZE, { 0.5f,0.5f });
	if ( hasDecor )
		ImGuiUtils::DrawTextureEx(*ImGui::GetBackgroundDrawList(), this->decor, this->pos + H_SQUARE_SIZE, { 0.5f,0.5f });
}

void Square::drawPos()
{
	char temp[20];
	sprintf(temp, "%.0f", (this->pos.y / SQUARE_SIZE));
	ImGui::GetBackgroundDrawList()->AddText(this->pos, WHITE, temp);
	sprintf(temp, "%.0f", (this->pos.x / SQUARE_SIZE));
	ImGui::GetBackgroundDrawList()->AddText(this->pos + H_SQUARE_SIZE, WHITE, temp);
}
