#include "menu.hpp"

#include "calc.hpp"

#define M this->purchaseMenu

Menu::Menu()
{
	for (int i = 0; i < 4; i++) this->purchaseMenu.tow[i];
	//this->font = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/EvilEmpire-4BBVK.ttf", 80);
	//this->font = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/Arneson-g3w6.ttf", 80);
	this->font = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/GlueGun-GW8Z.ttf", 80);
}

Menu::~Menu()
{
	for (int i = 0; i < 4; i++)
		if (M.tow[i]) delete M.tow[i];
}

void Menu::load(Type_Menu menu)
{
	this->mMenu = menu;
}

void Menu::loadPurchaseMenu(const Grid* g)
{
	// menu is hard placed
	M.tow[0] = new Basic;
	M.tow[1] = new Quick;
	M.tow[2] = new Slow;
	M.tow[3] = new Explosive;
	for (int i = 0; i < 4; i++)
		M.tow[i]->pos = g->square[20][16 + 2 * i].pos + H_SQUARE_SIZE;
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

// returns 1 if tower needs to be placed
// returns 2 if app is to be closed
// returns 11 if lvl 1 needs to be loaded
// returns 12 if lvl 2 etc
int Menu::update()
{
	if (this->mMenu == Type_Menu::IN_GAME) {
		if (!M.hasSelected && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			for (int i = 0; i < 4; i++)
				if (!M.hasSelected && M.tow[i]->isMouseOverTower()) {
					M.selection = *M.tow[i];
					M.hasSelected = true;
				}
		if (M.hasSelected && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
			M.selection.setPos(ImGui::GetMousePos().x, ImGui::GetMousePos().y);
		if (M.hasSelected && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
			M.hasSelected = false;
			return 1;
		}
	}
	else if (this->mMenu == Type_Menu::MAIN)
	{
		if (this->isButtonPressed({ H_WIDTH - 100, 250 }, { H_WIDTH + 100, 300 })) {// lvl 1 button
			this->mMenu = Type_Menu::LOADING;
			return 11;
		}
		if (this->isButtonPressed({ H_WIDTH - 100, 310 }, { H_WIDTH + 100, 355 })) {// lvl 2 button
			this->mMenu = Type_Menu::LOADING;
			return 12;
		}
		if (this->isButtonPressed({ H_WIDTH - 100, HEIGHT - 260 }, { H_WIDTH + 100, HEIGHT - 215 })) // exit button
			return 2;
	}
	return 0;
}

void Menu::draw(int currentLevel, int currentWave, int money)
{
	switch (this->mMenu)
	{
	case Type_Menu::LOADING:
		ImGui::GetBackgroundDrawList()->AddRectFilled({ 0,0 }, { WIDTH,HEIGHT }, SHY_LIGHT_BLUE);
		ImGui::GetBackgroundDrawList()->AddText(this->font, 60.f, { H_WIDTH - 100, H_HEIGHT - 50 }, WHITE, "LOADING...");
		break;
	case Type_Menu::MAIN:
		this->drawMain();
		break;
	case Type_Menu::IN_GAME:
		this->drawInGame(currentLevel, currentWave, money);
		if (M.hasSelected) M.selection.draw();
		break;
	case Type_Menu::PAUSE:
		break;
	case Type_Menu::VICTORY:
		break;
	case Type_Menu::LOSE:
		break;
	case Type_Menu::QUIT:
		break;

	default:
		break;
	}
}

void Menu::drawMain() const
{
	ImDrawList* dl = ImGui::GetBackgroundDrawList();
	dl->AddRectFilled({ 0,0 }, { WIDTH,HEIGHT }, SHY_LIGHT_BLUE);
	dl->AddText(this->font, 60.f, { H_WIDTH - 150, 150 }, WHITE, "TOWER DEFENSE");
	dl->AddRectFilled({ H_WIDTH - 100, 250 }, { H_WIDTH + 100, 300 }, WHITE, 3.f);
	dl->AddText(this->font, 40.f, { H_WIDTH - 60, 255 }, BLACK, "LEVEL N 1");
	dl->AddRectFilled({ H_WIDTH - 100, 310 }, { H_WIDTH + 100, 355 }, WHITE, 3.f);
	dl->AddText(this->font, 40.f, { H_WIDTH - 60, 315 }, BLACK, "LEVEL N 2");
	dl->AddRectFilled({ H_WIDTH - 100, HEIGHT - 260 }, { H_WIDTH + 100, HEIGHT - 215 }, WHITE, 3.f);
	dl->AddText(this->font, 40.f, { H_WIDTH - 65, HEIGHT - 255 }, BLACK, "EXIT GAME");
}

void Menu::drawInGame(int currentLevel, int currentWave, int money) const
{
	char tmp[50];
	ImDrawList* dl = ImGui::GetBackgroundDrawList();
	dl->AddRectFilled({ H_WIDTH - 7 * SQUARE_SIZE, HEIGHT - 2 * SQUARE_SIZE }, { H_WIDTH + 7 * SQUARE_SIZE, HEIGHT }, SHY_LIGHT_BLUE, 5.f);
	for (int i = 0; i < 4; i++) {
		M.tow[i]->draw(false);
		dl->AddText(this->font, 20.f, { (float)H_WIDTH + (2.f * (float)i - 4.f) * SQUARE_SIZE, (float)HEIGHT - SQUARE_SIZE }, BLACK, M.tow[i]->getTypeName());
		sprintf(tmp, "-%d c", M.tow[i]->price);
		dl->AddText(this->font, 18.f, { (float)H_WIDTH + (2.f * (float)i - 4.f) * SQUARE_SIZE, (float)HEIGHT - H_SQUARE_SIZE }, BLACK, tmp);
	}
	sprintf(tmp, "Level %d", currentLevel);
	dl->AddText(this->font, 20.f, { H_WIDTH - 7 * SQUARE_SIZE + 2.f, HEIGHT - 2 * SQUARE_SIZE + 4.f }, BLACK, tmp);
	sprintf(tmp, "Wave %d", currentWave);
	dl->AddText(this->font, 20.f, { H_WIDTH - 7 * SQUARE_SIZE + 2.f, HEIGHT - SQUARE_SIZE - H_SQUARE_SIZE / 2 }, BLACK, tmp);
	sprintf(tmp, "Cash %d", money);
	dl->AddText(this->font, 20.f, { H_WIDTH - 7 * SQUARE_SIZE + 2.f, HEIGHT - SQUARE_SIZE + H_SQUARE_SIZE / 2 + 4.f }, BLACK, tmp);
	dl->AddText(this->font, 20.f, { H_WIDTH + 4 * SQUARE_SIZE + 10.f, HEIGHT - 2 * SQUARE_SIZE + 4.f }, BLACK, "Castle life");
	// castle's life should draw under this
}