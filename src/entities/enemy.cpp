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

void Enemy::update(Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle)
{
	move(listCheckpoint, nbCheckpoint);
	if (this->checkId + 1 == nbCheckpoint)
		castle->health.health -= this->attackDmg;
}

void Enemy::draw()
{
	ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
	fgDrawlist->AddCircleFilled({ pos.x, pos.y }, 10, ImColor(1.f, 0.f, 0.f));
}

void Enemy::move(Checkpoint* listCheckpoint, int nbCheckpoint)
{
	//checkpoints change direction
	for (int i = 0; i < nbCheckpoint; ++i)
		if (listCheckpoint[i].id == this->checkId) {
			if (this->direction == RIGHT && this->pos.x + this->moveSpeed >= listCheckpoint[i].pos.x) {
				this->pos.x = listCheckpoint[i].pos.x;
				this->direction = listCheckpoint[i].newDirection;
				this->checkId++;
			}
			else if (this->direction == LEFT && this->pos.x - this->moveSpeed <= listCheckpoint[i].pos.x) {
				this->pos.x = listCheckpoint[i].pos.x;
				this->direction = listCheckpoint[i].newDirection;
				this->checkId++;
			}
			else	if (this->direction == DOWN && this->pos.y + this->moveSpeed <= listCheckpoint[i].pos.y) {
				this->pos.y = listCheckpoint[i].pos.y;
				this->direction = listCheckpoint[i].newDirection;
				this->checkId++;
			}
			else	if (this->direction == UP && this->pos.y - this->moveSpeed >= listCheckpoint[i].pos.y) {
				this->pos.y = listCheckpoint[i].pos.y;
				this->direction = listCheckpoint[i].newDirection;
				this->checkId++;
			}
			else
				this->pos += this->direction * this->moveSpeed;
		}
}