#include "square.hpp"
#include "../calc.hpp"

Square::Square()
{
	this->type = Type_Square::NONE;
	this->loadTexture("assets/towerDefense_tile015.png");
}

Square::~Square()
{
	this->unloadTexture();
}

void Square::setType(Type_Square type)
{
	this->type = type;
	switch (type)
	{
	case Type_Square::NONE:
		this->loadTexture("assets/towerDefense_tile015.png");
		break;
	case Type_Square::BACKGROUND:
		this->loadTexture("assets/towerDefense_tile103.png");
		break;
	case Type_Square::GRASS:
		this->canHaveTower = true; {
			int choiceGrass = (rand() % 4);
			if (choiceGrass == 0)
				this->loadTexture("assets/towerDefense_tile024.png");
			else if (choiceGrass == 1)
				this->loadTexture("assets/towerDefense_tile157.png");
			else if (choiceGrass == 2)
				this->loadTexture("assets/towerDefense_tile162.png");
			else if (choiceGrass == 3)
				this->loadTexture("assets/towerDefense_tile231.png"); }
		break;
	case Type_Square::PATH:
		//this->loadTexture("assets/towerDefense_tile158.png");
		this->loadTexture("assets/towerDefense_tile060.png");
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
	/*
	switch (type)
	{
	case Type_Square::NONE:
		ImGui::GetBackgroundDrawList()->AddRect({ this->pos.x, this->pos.y }, { this->pos.x + SQUARE_SIZE, this->pos.y + SQUARE_SIZE }, this->color);
		break;
	default:
		ImGui::GetBackgroundDrawList()->AddRectFilled({ this->pos.x, this->pos.y }, { this->pos.x + SQUARE_SIZE, this->pos.y + SQUARE_SIZE }, this->color);
		break;
	}*/
}

void Square::drawPos()
{
	char temp[20];
	sprintf(temp, "%.0f", (this->pos.y / SQUARE_SIZE));
	ImGui::GetBackgroundDrawList()->AddText(this->pos, WHITE, temp);
	sprintf(temp, "%.0f", (this->pos.x / SQUARE_SIZE));
	ImGui::GetBackgroundDrawList()->AddText(this->pos + H_SQUARE_SIZE, WHITE, temp);
}
