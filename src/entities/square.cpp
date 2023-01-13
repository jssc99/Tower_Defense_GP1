#include "square.hpp"
#include "../calc.hpp"

Square::Square()
{
	this->type = Type::NONE;
	this->color = WHITE;
	this->canHaveTower = false;
}

std::string Square::getType() const
{
	switch (this->type)
	{
	case Type::NONE:
		return "None";
	case Type::BACKGROUND:
		return "Decor";
	case Type::GRASS:
		return "Grass";
	case Type::PATH:
		return "Path";
	case Type::CASTLE:
		return "Castle";
	case Type::SPAWN:
		return "Spawn";
	default:
		return "error";
	}
}

void Square::setType(Type type)
{
	this->type = type;
	switch (type)
	{
	case Type::NONE:
		this->color = BLACK;
		break;
	case Type::BACKGROUND:
		this->color = RED;
		break;
	case Type::GRASS:
		this->canHaveTower = true;
		this->color = GREEN;
		break;
	case Type::PATH:
		this->color = ORANGE;
		break;
	case Type::CASTLE:
		this->color = VIOLET;
		break;
	case Type::SPAWN:
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

void Square::draw()
{
	switch (type)
	{
	case Type::NONE:
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
