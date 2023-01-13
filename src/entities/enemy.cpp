#include <imgui.h>

#include "enemy.hpp"
#include "../calc.hpp"
#include "../game.hpp"


Enemy::Enemy()
{
	this->attackDmg = 0;
	this->moveSpeed = 1;
	this->loot = 0;
	this->direction = RIGHT;
	this->checkId = 1;
}


void Enemy::update(Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle)
{
	if (this->checkId -1 != nbCheckpoint)
		this->move(listCheckpoint, nbCheckpoint);
	else
		castle->healthSystem.health -= this->attackDmg;
}

void Enemy::draw()
{
	ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
	fgDrawlist->AddCircleFilled({ pos.x, pos.y }, 10, this->color);
}

void Enemy::spawn(Grid* grid)
{
	this->pos = grid->getSpawnPoint();
}

void Enemy::move(Checkpoint* listCheckpoint, int nbCheckpoint)
{
	//checkpoints change direction
	for (int i = 0; i < nbCheckpoint; ++i)
	{
		if (listCheckpoint[i].id == this->checkId)
			if (this->pos.x >= listCheckpoint[i].pos.x - 5.f && 
				this->pos.x <= listCheckpoint[i].pos.x + 5.f && 
				this->pos.y >= listCheckpoint[i].pos.y - 5.f && 
				this->pos.y <= listCheckpoint[i].pos.y + 5.f)
			{
				this->direction = listCheckpoint[i].newDirection;
				this->checkId++;
			}
			else
				this->pos += this->direction * this->moveSpeed;
	}
}