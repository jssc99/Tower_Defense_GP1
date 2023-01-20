#include "menu.hpp"

#include "calc.hpp"

Menu::Menu()
{
	for (int i = 0; i < 4; i++) this->mPurchaseMenu.tow[i] = nullptr;
	//this->mFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/EvilEmpire-4BBVK.ttf", 80);
	//this->mFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/Arneson-g3w6.ttf", 80);
	this->mFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/GlueGun-GW8Z.ttf", 80);
}

Menu::~Menu()
{
	for (int i = 0; i < 4; i++)
		if (this->mPurchaseMenu.tow[i]) delete this->mPurchaseMenu.tow[i];
}

void Menu::setMenu(Type_Menu menu)
{
	this->mMenu = menu;
}

Type_Menu Menu::getMenu() const
{
	return this->mMenu;
}

Tower* Menu::getSelection()
{
	return &this->mPurchaseMenu.selection;
}

void Menu::loadPurchaseMenu(Grid* g)
{
	// menu is hard placed
	this->mPurchaseMenu.tow[0] = new Basic;
	this->mPurchaseMenu.tow[1] = new Quick;
	this->mPurchaseMenu.tow[2] = new Slow;
	this->mPurchaseMenu.tow[3] = new Explosive;
	for (int i = 0; i < 4; i++)
		this->mPurchaseMenu.tow[i]->pos = g->getSquareXY(20, 16 + 2 * i)->pos + H_SQUARE_SIZE;
}

void Menu::goToLoadingScreen()
{
	this->mMenu = Type_Menu::LOADING;
	this->draw();
}

bool Menu::isButtonPressed(const float2 x, const float2 y) const
{
	ImVec2 mouse = ImGui::GetMousePos();
	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) &&
		(x.x - (float)H_TOWER_SIZE <= mouse.x && mouse.x <= y.x + (float)H_TOWER_SIZE) &&
		(x.y - (float)H_TOWER_SIZE <= mouse.y && mouse.y <= y.y + (float)H_TOWER_SIZE))
		return true;
	else
		return false;
}

/***
returns 0 if nothing is needed
returns 1 if tower needs to be placed
returns 2 if app is to be closed
returns 3 if lvl is to be closed
returns 6 if speed is to changed to 0.5
returns 7 if speed is to changed to 1
returns 8 if speed is to changed to 2
returns 9 if lvl speed is to changed to 4
returns 11 if lvl 1 needs to be loaded
returns 12 if lvl 2 etc
***/
int Menu::update()
{
	switch (this->mMenu)
	{
	case Type_Menu::MAIN:
		return updateMain();
	case Type_Menu::IN_GAME:
		return this->updateInGame();
	case Type_Menu::PAUSE:
		return this->updatePause();
	case Type_Menu::VICTORY:
	case Type_Menu::LOSE:
		if (this->isButtonPressed(MAIN_BUT_EXIT_TOP, MAIN_BUT_EXIT_BOT) || ImGui::IsKeyPressed(ImGuiKey_Escape, false)) {
			this->goToLoadingScreen();
			return 3;
		}
		break;
	default:
		break;
	}
	return 0;
}

void Menu::draw(int currentLevel, int currentWave, int money, int towerPlaced, float gameSpeed)
{
	switch (this->mMenu)
	{
	case Type_Menu::LOADING:
		ImGui::GetForegroundDrawList()->AddRectFilled({ 0,0 }, { WIDTH,HEIGHT }, SHY_LIGHT_BLUE);
		ImGui::GetForegroundDrawList()->AddText(this->mFont, 60.f, { H_WIDTH - 100, H_HEIGHT - 50 }, WHITE, "LOADING...");
		break;
	case Type_Menu::MAIN:
		this->drawMain();
		break;
	case Type_Menu::IN_GAME:
		this->drawInGame(currentLevel, currentWave, money, towerPlaced, gameSpeed);
		if (this->mPurchaseMenu.hasSelected) this->mPurchaseMenu.selection.draw();
		break;
	case Type_Menu::PAUSE:
		this->drawPause();
		break;
	case Type_Menu::VICTORY:
		this->drawEnd(true);
		break;
	case Type_Menu::LOSE:
		this->drawEnd(false);
		break;

	default:
		break;
	}
}

int Menu::updateMain()
{
	if (this->isButtonPressed(MAIN_BUT_ONE_TOP, MAIN_BUT_ONE_BOT)) {// lvl 1 button
		this->goToLoadingScreen();
		return 11;
	}
	else if (this->isButtonPressed(MAIN_BUT_TWO_TOP, MAIN_BUT_TWO_BOT)) {// lvl 2 button
		this->goToLoadingScreen();
		return 12;
	}
	else if (this->isButtonPressed(MAIN_BUT_EXIT_TOP, MAIN_BUT_EXIT_BOT) || ImGui::IsKeyPressed(ImGuiKey_Escape, false)) // exit button
		return 2;
	return 0;
}

int Menu::updateInGame()
{
	if (this->isButtonPressed({ H_WIDTH - 1 * SQUARE_SIZE + 2.f, 0 }, { H_WIDTH - 0 * SQUARE_SIZE + 2.f, 20.f }))
		return 6;				  										  
	if (this->isButtonPressed({ H_WIDTH + 1 * SQUARE_SIZE + 2.f, 0 }, { H_WIDTH + 2 * SQUARE_SIZE + 2.f, 20.f }))
		return 7;
	if (this->isButtonPressed({ H_WIDTH + 3 * SQUARE_SIZE + 2.f, 0 }, { H_WIDTH + 4 * SQUARE_SIZE + 2.f, 20.f }))
		return 8;
	if (this->isButtonPressed({ H_WIDTH + 5 * SQUARE_SIZE + 2.f, 0 }, { H_WIDTH + 6 * SQUARE_SIZE + 2.f, 20.f }))
		return 9;
	if (!this->mPurchaseMenu.hasSelected && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		for (int i = 0; i < 4; i++)
			if (!this->mPurchaseMenu.hasSelected && this->mPurchaseMenu.tow[i]->isMouseOverTower()) {
				this->mPurchaseMenu.selection = *this->mPurchaseMenu.tow[i];
				this->mPurchaseMenu.hasSelected = true;
			}
	if (this->mPurchaseMenu.hasSelected && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
		this->mPurchaseMenu.selection.setPos(ImGui::GetMousePos().x, ImGui::GetMousePos().y);
	if (this->mPurchaseMenu.hasSelected && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
		this->mPurchaseMenu.hasSelected = false;
		return 1;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_Escape, false) || ImGui::IsKeyPressed(ImGuiKey_Space, false))
		this->mMenu = Type_Menu::PAUSE;
	return 0;
}

int Menu::updatePause()
{
	if (this->isButtonPressed(MAIN_BUT_ONE_TOP, MAIN_BUT_ONE_BOT) || ImGui::IsKeyPressed(ImGuiKey_Space, false))
		this->mMenu = Type_Menu::IN_GAME;
	if (this->isButtonPressed(MAIN_BUT_EXIT_TOP, MAIN_BUT_EXIT_BOT) || ImGui::IsKeyPressed(ImGuiKey_Escape, false)) {
		this->goToLoadingScreen();;
		return 3;
	}
	return 0;
}

void Menu::drawExitButton(ImDrawList* dl, bool mainMenu) const {
	dl->AddRectFilled(MAIN_BUT_EXIT_TOP, MAIN_BUT_EXIT_BOT, WHITE, 3.f);
	if (mainMenu)
		dl->AddText(this->mFont, 40.f, { H_WIDTH - 65, HEIGHT - 255 }, BLACK, "MAIN MENU");
	else
		dl->AddText(this->mFont, 40.f, { H_WIDTH - 65, HEIGHT - 255 }, BLACK, "EXIT GAME");
}

void Menu::drawMain() const
{
	ImDrawList* dl = ImGui::GetForegroundDrawList();
	ImGui::GetBackgroundDrawList()->AddRectFilled({ 0,0 }, { WIDTH,HEIGHT }, SHY_LIGHT_BLUE);
	dl->AddText(this->mFont, 80.f, { H_WIDTH - 200, 150 }, WHITE, "TOWER DEFENSE");
	dl->AddRectFilled(MAIN_BUT_ONE_TOP, MAIN_BUT_ONE_BOT, WHITE, 3.f);
	dl->AddText(this->mFont, 40.f, { H_WIDTH - 60, 255 }, BLACK, "LEVEL N 1");
	dl->AddRectFilled(MAIN_BUT_TWO_TOP, MAIN_BUT_TWO_BOT, WHITE, 3.f);
	dl->AddText(this->mFont, 40.f, { H_WIDTH - 60, 315 }, BLACK, "LEVEL N 2");
	this->drawExitButton(dl, false);
}

void Menu::drawInGame(int currentLevel, int currentWave, int money, int towerPlaced, float gameSpeed) const
{
	ImDrawList* dl = ImGui::GetForegroundDrawList();
	ImGui::GetBackgroundDrawList()->AddRectFilled({ H_WIDTH - 7 * SQUARE_SIZE, 0 }, { H_WIDTH + 7 * SQUARE_SIZE, SQUARE_SIZE}, SHY_LIGHT_BLUE, 5.f);
	dl->AddText(this->mFont, 20.f, { 2.f, 0 }, BLACK, "Spacebar to pause");
	dl->AddText(this->mFont, 20.f, { H_WIDTH - 7 * SQUARE_SIZE + 2.f, 0 }, BLACK, "Change Game Speed");
	dl->AddText(this->mFont, 20.f, { H_WIDTH - 1 * SQUARE_SIZE + 2.f, 0 }, ( gameSpeed == 0.5f ? WHITE : BLACK ), "0.5");
	dl->AddText(this->mFont, 20.f, { H_WIDTH + 1 * SQUARE_SIZE + 2.f, 0 }, ( gameSpeed == 1.f ? WHITE : BLACK ), "1");
	dl->AddText(this->mFont, 20.f, { H_WIDTH + 3 * SQUARE_SIZE + 2.f, 0 }, ( gameSpeed == 2.f ? WHITE : BLACK ), "2");
	dl->AddText(this->mFont, 20.f, { H_WIDTH + 5 * SQUARE_SIZE + 2.f, 0 }, ( gameSpeed == 4.f ? WHITE : BLACK ), "4");
	char tmp[50];
	ImGui::GetBackgroundDrawList()->AddRectFilled({ H_WIDTH - 7 * SQUARE_SIZE, HEIGHT - 2 * SQUARE_SIZE }, { H_WIDTH + 7 * SQUARE_SIZE, HEIGHT }, SHY_LIGHT_BLUE, 5.f);
	for (int i = 0; i < 4; i++) {
		this->mPurchaseMenu.tow[i]->draw(false);
		dl->AddText(this->mFont, 20.f, { (float)H_WIDTH + (2.f * (float)i - 4.f) * SQUARE_SIZE, (float)HEIGHT - SQUARE_SIZE }, BLACK, this->mPurchaseMenu.tow[i]->getTypeName());
		sprintf(tmp, "-%d c", this->mPurchaseMenu.tow[i]->getPrice());
		dl->AddText(this->mFont, 18.f, { (float)H_WIDTH + (2.f * (float)i - 4.f) * SQUARE_SIZE, (float)HEIGHT - H_SQUARE_SIZE }, BLACK, tmp);
	}
	// left side
	sprintf(tmp, "level %d", currentLevel);
	dl->AddText(this->mFont, 20.f, { H_WIDTH - 7 * SQUARE_SIZE + 2.f, HEIGHT - 2 * SQUARE_SIZE + 4.f }, BLACK, tmp);
	sprintf(tmp, "wave %d", currentWave);
	dl->AddText(this->mFont, 20.f, { H_WIDTH - 7 * SQUARE_SIZE + 2.f, HEIGHT - SQUARE_SIZE - H_SQUARE_SIZE / 2 }, BLACK, tmp);
	sprintf(tmp, "cash %d", money);
	dl->AddText(this->mFont, 20.f, { H_WIDTH - 7 * SQUARE_SIZE + 2.f, HEIGHT - SQUARE_SIZE + H_SQUARE_SIZE / 2 + 4.f }, BLACK, tmp);
	// right side
	dl->AddText(this->mFont, 20.f, { H_WIDTH + 4 * SQUARE_SIZE + 10.f, HEIGHT - 2 * SQUARE_SIZE + 4.f }, BLACK, "castles life");
	// castle's life should draw here
	sprintf(tmp, "%d / %d", towerPlaced, MAX_NB_TOWERS);
	dl->AddText(this->mFont, 20.f, { H_WIDTH + 10 * H_SQUARE_SIZE, HEIGHT - SQUARE_SIZE + 6.f }, BLACK, tmp);
}

void Menu::drawPause() const
{
	ImDrawList* dl = ImGui::GetForegroundDrawList();
	ImGui::GetBackgroundDrawList()->AddRectFilled({ 0,0 }, { WIDTH,HEIGHT }, SHY_LIGHT_BLUE);
	dl->AddText(this->mFont, 30.f, { 140.f, 200.f }, BLACK, "Usefull tips:");
	dl->AddText(this->mFont, 30.f, { 140.f, 250.f }, BLACK, "Double click to");
	dl->AddText(this->mFont, 30.f, { 140.f, 290.f }, BLACK, "upgrade a Tower");
	dl->AddText(this->mFont, 30.f, { 140.f, 330.f }, BLACK, "(15c each,");
	dl->AddText(this->mFont, 30.f, { 140.f, 370.f }, BLACK, "5 upgrades max)");
	dl->AddText(this->mFont, 30.f, { 140.f, 410.f }, BLACK, "Max 50 Towers");
	dl->AddText(this->mFont, 30.f, { 140.f, 450.f }, BLACK, "can be placed.");
	dl->AddText(this->mFont, 60.f, { H_WIDTH - 60, 150 }, WHITE, "PAUSE");
	dl->AddRectFilled(MAIN_BUT_ONE_TOP, MAIN_BUT_ONE_BOT, WHITE, 3.f);
	dl->AddText(this->mFont, 40.f, { H_WIDTH - 60, 255 }, BLACK, "UNPAUSE");
	this->drawExitButton(dl, true);
}

void Menu::drawEnd(bool victory) const
{
	ImDrawList* dl = ImGui::GetForegroundDrawList();
	ImGui::GetBackgroundDrawList()->AddRectFilled({ 0,0 }, { WIDTH,HEIGHT }, SHY_LIGHT_BLUE);
	if (victory)
		dl->AddText(this->mFont, 60.f, { H_WIDTH - 60, 150 }, WHITE, "VICTORY");
	else
		dl->AddText(this->mFont, 60.f, { H_WIDTH - 60, 150 }, WHITE, "DEFEAT");
	this->drawExitButton(dl, true);
}