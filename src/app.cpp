#include "app.hpp"

#include <stdio.h>

App::App()
{
	// grid test

	this->grid.square[0][1].setType(BACKGROUND);
	this->grid.square[10][0].setType(SPAWN);
	this->grid.square[10][1].setType(GRASS);

	//enemy test
	
	e.pos = this->grid.getSpawnPoint();
	e.moveSpeed = 1.f;
	e.direction = RIGHT;

	//checkpoint test
	nbrCheck = 5;
	check[0].pos = this->grid.square[10][10].pos;
	check[0].newDirection = UP;
	check[1].pos = this->grid.square[5][10].pos;
	check[1].newDirection = RIGHT;
	check[2].pos = this->grid.square[5][17].pos;
	check[2].newDirection = DOWN;
	check[3].pos = this->grid.square[12][17].pos;
	check[3].newDirection = RIGHT;
	check[4].pos = this->grid.square[12][22].pos;
	check[4].newDirection = STOP;
}

App::~App()
{
}

void App::Update()
{	
	{
		ImGui::Begin("Tower");
		ImGui::Text("Enemy pos = %f, %f", e.pos.x, e.pos.y);
		ImGui::SliderFloat("Enemy ms", &e.moveSpeed, 0.1f, 10.0f);
		if (ImGui::Button("Right"))
			e.direction = RIGHT;
		if (ImGui::Button("Left"))
			e.direction = LEFT;
		if (ImGui::Button("Up"))
			e.direction = UP;
		if (ImGui::Button("Down"))
			e.direction = DOWN;
		if (ImGui::Button("Stop"))
			e.direction = STOP;

		ImGui::Text("square id %d:", this->grid.square[0][1].id);
		ImGui::Text("square type %s", this->grid.square[0][1].getType());
		
		ImGui::Text("square id %d:", this->grid.square[10][1].id);
		ImGui::Text("square type %s", this->grid.square[10][1].getType());

		ImGui::Text("checkpoint[0] pos %f, %f", check[0].pos.x, check[0].pos.y);
		ImGui::Text("checkpoint[1] pos %f, %f", check[1].pos.x, check[1].pos.y);
		ImGui::Text("checkpoint[2] pos %f, %f", check[2].pos.x, check[2].pos.y);
		ImGui::Text("checkpoint[3] pos %f, %f", check[3].pos.x, check[3].pos.y);
		ImGui::Text("checkpoint[4] pos %f, %f", check[4].pos.x, check[4].pos.y);
		ImGui::End();
	}
	this->grid.drawGrid();

	e.drawEntity();
	e.pos += e.direction * e.moveSpeed;

	//checkpoint test
	for (int i = 0; i < nbrCheck; ++i)
	{
		check[i].drawEntity();
		if (e.pos.x >= check[i].pos.x-5.f && e.pos.x <= check[i].pos.x+5.f && e.pos.y >= check[i].pos.y - 5.f && e.pos.y <= check[i].pos.y + 5.f)
		{
			e.direction = check[i].newDirection;
		}
	}
}