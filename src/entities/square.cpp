#include "square.hpp"
#include "../calc.hpp"

Square::Square()
{
	this->type = Type::NONE;
	this->color = WHITE;
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
	ImDrawList& bgDrawlist = *ImGui::GetBackgroundDrawList();
	switch (type)
	{
	case Type::NONE:
		bgDrawlist.AddRect({ this->pos.x, this->pos.y }, { this->pos.x + SQUARE_SIZE, this->pos.y + SQUARE_SIZE }, this->color);
		break;

	default:
		bgDrawlist.AddRectFilled({ this->pos.x, this->pos.y }, { this->pos.x + SQUARE_SIZE, this->pos.y + SQUARE_SIZE }, this->color);
		break;
	}
	char* temp = new char;
	sprintf(temp, "%.0f", (this->pos.y / SQUARE_SIZE));
	bgDrawlist.AddText({ this->pos.x, this->pos.y }, WHITE, temp);
	sprintf(temp, "%.0f", (this->pos.x / SQUARE_SIZE));
	bgDrawlist.AddText({ this->pos.x + H_SQUARE_SIZE, this->pos.y + H_SQUARE_SIZE }, WHITE, temp);
}