#include "app.hpp"

#include <stdio.h>

App::App()
{
	std::string lvl1 =  std::string("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")+
												"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
												"bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
												"bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
												"ggggggggggggggggbbbbccpppppppppgggggggbb" +
												"ggggggggggggggggbbbbccpppppppppgggggggbb" +
												"spppppppgggggggggggggggggggggppgggggggbb" +
												"ppppppppgggggggggggggggggggggppgggggggbb" +
												"ggggggppggggggggbbgggggggggggppgggggggbb" +
												"ggggggppggggggggbbgggggggggggppgggggggbb" +
												"ggggggppggggggggbbgggggggggggppgggggggbb" +
												"ggggggppggggggggbbbbgggggggggppgggggggbb" +
												"ggggggppggggggggbbbbgggggggggppgggggggbb" +
												"ggggggppggggggggbbbbgggggggggppgggggggbb" +
												"ggggggppggggggggggbbbbgggggggppgggggggbb" +
												"ggggggppggggggggggbbbbgggggggppgggggggbb" +
												"bbggggpppppppppppppppppppppppppgggggggbb" +
												"bbggggpppppppppppppppppppppppppgggggggbb" +
												"bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
												"bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
												"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
												"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" ;
	this->grid.loadGrid(lvl1);
	int id = 0;
	Checkpoint list[6] ={
	    {++id, { 6,7 }, DOWN },
		{++id, { 16,7 }, RIGHT},
		{++id, { 16,30 }, UP},
		{++id, { 4,30 }, LEFT},
		{++id, { 4,21 }, STOP} };
	this->grid.loadCheckpoints(list, id);
}

App::~App()
{
}

void App::Update()
{
	{
		ImGui::Begin("Tower");
		ImGui::End();
	}
}