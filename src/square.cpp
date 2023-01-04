#include "square.hpp"

Square::Square(Type type = NONE) : type(type)
{
	this->id = _id++;
	this->canPlaceTower = false;
	this->hasCheckpoint = false;
	this->color = ImColor(0.f, 0.f, 0.f, 0.f);
	this->checkpoint = { 0, UP };

	switch (type)
	{
	case NONE:
		this->color = ImColor( 0.f ,0.f, 0.f, 1.f );
		break;
	case BACKGROUND:
		this->color = ImColor(1.f, 0.f, 0.f, 1.f);
		break;
	case GRASS:
		this->color = ImColor(0.f, 1.f, 0.f, 1.f);
		this->canPlaceTower = true;
		break;
	case PATH:
		this->color = ImColor(1.f, 1.f, 0.f, 1.f);
		break;
	case CASTLE:
		this->color = ImColor(1.f, 0.f, 1.f, 1.f);
		break;
	default:
		break;
	}
}

std::string Square::getType()
{
	switch (this->type)
	{
	case NONE:
		return (std::string)"None";
	case BACKGROUND:
		return (std::string)"Background";
	case GRASS:
		return (std::string)"Grass";
	case PATH:
		return (std::string)"Path";
	case CASTLE:
		return (std::string)"Castle";
	default:
		return (std::string)"error";
	}
}

void Square::drawEntity()
{
	ImDrawList& bgDrawlist = *ImGui::GetBackgroundDrawList();

	switch (type)
	{
	case NONE:
		bgDrawlist.AddRect({ this->pos.x - 16, this->pos.y - 16 }, { this->pos.x + 16, this->pos.y + 16 }, this->color);
		break;

	case BACKGROUND:
	case GRASS:
	case PATH:
	case CASTLE:
		bgDrawlist.AddRectFilled({ this->pos.x - 16, this->pos.y - 16 }, { this->pos.x + 16, this->pos.y + 16 }, this->color);
		break;

	default:
		break;
	}
}