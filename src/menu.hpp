#pragma once

#include "grid.hpp"
#include "entities/sub_enemies.hpp"
#include "entities/sub_towers.hpp"

#define MAIN_BUT_ONE_TOP { H_WIDTH - 100, 250 }
#define MAIN_BUT_ONE_BOT { H_WIDTH + 100, 300 }
#define MAIN_BUT_TWO_TOP { H_WIDTH - 100, 310 }
#define MAIN_BUT_TWO_BOT { H_WIDTH + 100, 355 }
#define MAIN_BUT_EXIT_TOP { H_WIDTH - 100, HEIGHT - 260 }
#define MAIN_BUT_EXIT_BOT { H_WIDTH + 100, HEIGHT - 215 }

enum class Type_Menu : char
{
	NONE = 'n',
	LOADING = 'b', // 'b'eginning
	MAIN = 'm',
	IN_GAME = 'g',
	PAUSE = 'p',
	VICTORY = 'v',
	LOSE = 'l'
	//QUIT = 'q'
};

struct purchaseMenu
{
	Tower* tow[4];
	Tower selection;
	bool hasSelected = false;
};

class Menu
{
public:
	ImFont* font;
	purchaseMenu purchaseMenu;

	Menu();
	~Menu();

	void setMenu(Type_Menu menu);
	Type_Menu getMenu() const;

	void loadPurchaseMenu(const Grid* g);
	void goToLoadingScreen();

	bool isButtonPressed(const float2 x, const float2 y) const;

	int update();
	void draw(int currentLevel = 0, int currentWave = 0, int money = 0, int towerPlaced = 0);

private:
	Type_Menu mMenu = Type_Menu::NONE;

	int updateMain();
	int updateInGame();
	int updatePause();

	void drawMain() const;
	void drawInGame(int currentLevel, int currentWave, int money, int towerPlaced) const;
	void drawPause() const;
	void drawEnd(bool victory) const;

	void drawExitButton(ImDrawList* dl, bool mainMenu) const;
};