#include "app.hpp"

#include <stdio.h>

App::App()
{
	//enemy test
	e.moveSpeed = 1.f;
	e.direction = RIGHT;
	this->grid.square[10][0].setType(SPAWN);
	e.pos = this->grid.square[10][0].pos;

	// grid test
	this->grid.square[0][1].setType(BACKGROUND);
	this->grid.square[10][1].setType(GRASS);
}

App::~App()
{
}

void App::Update()
{
	{
		ImGui::Begin("Tower");
		ImGui::Text("e.pos = %f, %f", e.pos.x, e.pos.y);
		ImGui::SliderFloat("move speed = ", &e.moveSpeed, 0.1f, 10.f);
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

		ImGui::Text("\n");
		ImGui::Text("square id %d:", this->grid.square[0][1].id);
		ImGui::Text("square type %s", this->grid.square[0][1].getType());
		
		ImGui::Text("square id %d:", this->grid.square[10][1].id);
		ImGui::Text("square type %s", this->grid.square[10][1].getType());
		ImGui::End();
	}

	this->grid.drawGrid();
	e.drawEntity();
	e.pos += e.direction * e.moveSpeed;
}