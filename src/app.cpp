#include "app.hpp"

#include <stdio.h>

App::App()
{
	// grid test
	std::string lvl1 =  std::string("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")+
												"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
												"bbbggggggggggggbbbbbbbbggggggggggbbbbbbb" +
												"bggggggggggggggggbbgggggggggcggggggggggb" +
												"gggggggggggggggggggggggggggpppgggggggggg" +
												"pppppppppggggggggggggggggggpppgggggggggg" +
												"sppppppppggggggggggggggggggpppgggggggggg" +
												"pppppppppggggggggggggggggggpppgggggggggg" +
												"ggggggpppggggggggggggggggggpppgggggggggg" +
												"ggggggpppggggggggggggggggggpppgggggggggg" +
												"ggggggpppggggggggbbggggggggpppgggggggggg" +
												"ggggggpppgggggggbbbggggggggpppgggggggggg" +
												"ggggggpppgggggggbbbbgggggggpppgggggggggg" +
												"ggggggpppgggggggggbbgggggggpppgggggggggg" +
												"ggggggpppggggggggggggggggggpppgggggggggg" +
												"ggggggppppppppppppppppppppppppgggggggggg" +
												"ggggggppppppppppppppppppppppppgggggggggg" +
												"ggggggppppppppppppppppppppppppgggggggggg" +
												"gggggggggggggggggggggggggggggggggggggggg" +
												"gggggggggggggggggggggggggggggggggggggggg" +
												"bbbggggggggggggbbbbbbbbggggggggggbbbbbbb" +
												"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" ;
	this->grid.loadGrid(lvl1);
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

		ImGui::Text("square id %d:", this->grid.square[0][1].id);
		ImGui::Text("square type %s", this->grid.square[0][1].getType());

		ImGui::Text("square id %d:", this->grid.square[10][1].id);
		ImGui::Text("square type %s", this->grid.square[10][1].getType());
		ImGui::End();
	}
	this->grid.drawGrid();
}