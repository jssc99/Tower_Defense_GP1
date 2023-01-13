#include "app.hpp"

#include <stdio.h>

#define G this->game

App::App()
{
	// grid test

	std::string lvl1 = std::string("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")+
								   "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
								   "bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
								   "bbbbggggggggggbbbbbbbbgggggggggggbbbbbbb" +
								   "ggggggggggggggggbbbbccpppppppppgggggggbb" +
								   "ggggggggggggggggbbbbccpppppppppgggggggbb" +
								   "ppppppppgggggggggggggggggggggppgggggggbb" +
								   "spppppppgggggggggggggggggggggppgggggggbb" +
								   "ggggggppggggggggbbgggggggggggppgggggggbb" +
								   "ggggggppggggggggbbgggggggggggppgggggggbb" +
								   "ggggggppggggggggbbgggggggggggppgggggggbb" +
								   "ggggggppggggggggbbbbgggggggggppgggggggbb" +
								   "ggggggppppppppppppppgggggggggppgggggggbb" +
								   "ggggggppppppppppppppgggggggggppgggggggbb" +
								   "ggggggppggggggggggppbbgggggggppgggggggbb" +
								   "ggggggppggggggggggppbbgggggggppgggggggbb" +
								   "bbggggpppppppppppppppppppppppppgggggggbb" +
								   "bbggggpppppppppppppppppppppppppgggggggbb" +
								   "bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
								   "bbbbggggggggggggggbbbbggggggggggggbbbbbb" +
								   "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" +
								   "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
	int id = 9;
	Checkpoint list[9] = {
		{++id, { 6,7 }, DOWN },
		{++id, { 16,7 }, RIGHT},
		{++id, { 16,19}, UP},
		{++id, { 12,19}, LEFT},
		{++id, { 12,7}, DOWN},
		{++id, { 16,7 }, RIGHT},
		{++id, { 16,30 }, UP},
		{++id, { 4,30 }, LEFT},
		{++id, { 4,21 }, STOP}
	};
	G.load(lvl1, list, id);

}

App::~App()
{
}

void App::Update()
{	
	G.update();
}