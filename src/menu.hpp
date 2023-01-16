#pragma once

#include "grid.hpp"
#include "entities/enemies/healer.hpp"
#include "entities/enemies/knight.hpp"
#include "entities/enemies/soldier.hpp"
#include "entities/towers/slow_tower.hpp"
#include "entities/towers/basic_tower.hpp"
#include "entities/towers/quick_tower.hpp"
#include "entities/towers/explosive_tower.hpp"

enum class Type_Menu : char
{
	NONE = 'n',
	LOADING = 'b', // 'b'eginning
	MAIN = 'm',
	IN_GAME = 'g',
	PAUSE = 'p',
	VICTORY = 'v',
	LOSE = 'l',
	QUIT = 'q'
};

struct purchaseMenu
{
	Tower* tow[4];
	Tower selection;
	bool hasSelected;
};

class Menu
{
public:
	ImFont* font;
	purchaseMenu purchaseMenu;

	Menu();
	~Menu();

	void load(Type_Menu menu);
	void loadPurchaseMenu(Grid* g);

	int update();
	void draw(Grid *g = nullptr);

private:
	Type_Menu mMenu;
};