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
	this->healthSystem.maxHealth = 0;
	this->healthSystem.health = 0;
}


void Enemy::update(Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle)
{
	if (this->checkId -1 != nbCheckpoint)
		this->move(listCheckpoint, nbCheckpoint);
	else
		if(castle->healthSystem.health - this->attackDmg >= 0)
			castle->healthSystem.health -= this->attackDmg;
	if (this->healthSystem.health <= 0)
		this->die();
}

void Enemy::draw()
{
	ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
	fgDrawlist->AddCircleFilled({ pos.x, pos.y }, 10, this->color);
}

void Enemy::drawHealth()
{
	ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
	fgDrawlist->AddRectFilled({ pos.x - (healthSystem.health * L_HEALTH_SIZE/2) / healthSystem.maxHealth, pos.y - 30 }, { pos.x + (healthSystem.health * L_HEALTH_SIZE/2) / healthSystem.maxHealth, pos.y - H_HEALTH_SIZE - 30 }, BLACK);
};

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
		{
			if (this->pos.x >= listCheckpoint[i].pos.x - 5.f &&
				this->pos.x <= listCheckpoint[i].pos.x + 5.f &&
				this->pos.y >= listCheckpoint[i].pos.y - 5.f &&
				this->pos.y <= listCheckpoint[i].pos.y + 5.f)
			{
				this->direction = listCheckpoint[i].newDirection;
				this->checkId++;
				this->healthSystem.health -= 10;
			}
			else
				this->pos += this->direction * this->moveSpeed;
		}
	}
}

void Enemy::die()
{
}
