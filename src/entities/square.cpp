#include "square.hpp"
#include "../calc.hpp"

Square::Square()
{
	this->type = Type_Square::NONE;
	this->color = WHITE;
	this->canHaveTower = false;
}

std::string Square::getType() const
{
	switch (this->type)
	{
	case Type_Square::NONE:
		return "None";
	case Type_Square::BACKGROUND:
		return "Decor";
	case Type_Square::GRASS:
		return "Grass";
	case Type_Square::PATH:
		return "Path";
	case Type_Square::CASTLE:
		return "Castle";
	case Type_Square::SPAWN:
		return "Spawn";
	default:
		return "error";
	}
}

void Square::setType(Type_Square type)
{
	this->type = type;
	switch (type)
	{
	case Type_Square::NONE:
		this->color = BLACK;
		break;
	case Type_Square::BACKGROUND:
		this->color = RED;
		break;
	case Type_Square::GRASS:
		this->canHaveTower = true;
		this->color = GREEN;
		break;
	case Type_Square::PATH:
		this->color = ORANGE;
		break;
	case Type_Square::CASTLE:
		this->color = VIOLET;
		break;
	case Type_Square::SPAWN:
		this->color = BLUE;
		break;
	default:
		break;
	}
}

float2 Square::getPosCenter() const
{
	return this->pos + H_SQUARE_SIZE;
}

bool Square::canPlaceTower()
{
	if (this->type == Type_Square::GRASS && this->canHaveTower)
		return true;
	else
		return false;
}

void Square::draw()
{
	switch (type)
	{
	case Type_Square::NONE:
		ImGui::GetBackgroundDrawList()->AddRect({ this->pos.x, this->pos.y }, { this->pos.x + SQUARE_SIZE, this->pos.y + SQUARE_SIZE }, this->color);
		break;

	default:
		ImGui::GetBackgroundDrawList()->AddRectFilled({ this->pos.x, this->pos.y }, { this->pos.x + SQUARE_SIZE, this->pos.y + SQUARE_SIZE }, this->color);
		break;
	}
}

void Square::drawPos()
{
	char* temp = new char;
	sprintf(temp, "%.0f", (this->pos.y / SQUARE_SIZE));
	ImGui::GetBackgroundDrawList()->AddText({ this->pos.x, this->pos.y }, WHITE, temp);
	sprintf(temp, "%.0f", (this->pos.x / SQUARE_SIZE));
	ImGui::GetBackgroundDrawList()->AddText({ this->pos.x + H_SQUARE_SIZE, this->pos.y + H_SQUARE_SIZE }, WHITE, temp);
}