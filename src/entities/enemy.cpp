#include <imgui.h>

#include "enemy.hpp"
#include "../calc.hpp"

Enemy::Enemy()
{
	this->attackDmg = 0;
	this->moveSpeed = 0;
	this->loot = 0;
	this->direction = RIGHT;
	this->checkId = 1;
}


void Enemy::setPos(float2 pos)
{
	this->pos = pos;
}

void Enemy::update(Grid* grid, Castle* castle, int nbEnemies)
{
	if (nbEnemies)
	{
		mMove(grid, castle, nbEnemies);
	}
}

void Enemy::draw()
{
	ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
	fgDrawlist->AddCircleFilled({ pos.x, pos.y }, 10, ImColor(1.f, 0.f, 0.f));
}

void Enemy::mMove(Grid* grid, Castle* castle, int nbEnemies)
{
	if (nbEnemies)
	{
		this->pos += this->direction * this->moveSpeed;
		//checkpoints change direction
		for (int i = 0; i < grid->nbCheckpoints; ++i)
		{
			if (this->pos.x >= grid->chkpList[i].pos.x - 5.f && this->pos.x <= grid->chkpList[i].pos.x + 5.f && this->pos.y >= grid->chkpList[i].pos.y - 5.f && this->pos.y <= grid->chkpList[i].pos.y + 5.f && grid->chkpList[i].id == this->checkId)
			{
				this->direction = grid->chkpList[i].newDirection;
				this->checkId++;
				//castle test
				if (i + 1 == grid->nbCheckpoints)//==last checkpoint(castle)
				{
					castle->health.health -= this->attackDmg;
				}
			}
		}
	}
}