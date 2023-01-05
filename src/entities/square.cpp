#include "square.hpp"

#define stringify( name ) #name

Square::Square(Type type) : type(type)
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

Square::Square()
{
	this->type = NONE;
}

std::string Square::getType()
{
	return stringify(this->type);
}

void Square::setType(Type type)
{
	this->type = type;

	switch (type)
	{
	case NONE:
		this->color = ImColor(0.f, 0.f, 0.f, 1.f);
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

void Square::drawEntity()
{
	ImDrawList& bgDrawlist = *ImGui::GetBackgroundDrawList();
	
	switch (type)
	{
	case NONE:
		bgDrawlist.AddRect({ this->pos.x - 16, this->pos.y - 16 }, { this->pos.x + 16, this->pos.y + 16 }, this->color);
		break;

	default:
		bgDrawlist.AddRectFilled({ this->pos.x - 16, this->pos.y - 16 }, { this->pos.x + 16, this->pos.y + 16 }, this->color);
		break;
	}
	char* nb = new char;
	sprintf(nb, "%d", this->id);
	bgDrawlist.AddText({ this->pos.x - 16.f, this->pos.y }, ImColor(1.f, 1.f, 1.f, 1.f), nb);
}