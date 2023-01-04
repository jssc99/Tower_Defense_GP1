#include "app.hpp"

#include "imgui_utils.hpp"

App::App()
{
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
		ImGui::Text("square id %d:", this->grid.square[0][1].id);
		ImGui::Text("square type %s", this->grid.square[0][1].getType());
		
		ImGui::Text("square id %d:", this->grid.square[10][1].id);
		ImGui::Text("square type %s", this->grid.square[10][1].getType());
		ImGui::End();
	}
	this->grid.drawGrid();
}