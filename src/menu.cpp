#include "menu.hpp"

#define M this->purchaseMenu

Menu::Menu()
{
	this->mMenu = Type_Menu::NONE;
	this->font = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/EvilEmpire-4BBVK.ttf", 80);
}

Menu::~Menu()
{
	for (int i = 0; i < 4; i++)
		if (M.tow[i])
			delete M.tow[i];
}

void Menu::load(Type_Menu menu)
{
	this->mMenu = menu;
}

void Menu::loadPurchaseMenu(Grid* g)
{
	// menu is hard placed
	M.tow[0] = new Basic;
	M.tow[1] = new Quick;
	M.tow[2] = new Slow;
	M.tow[3] = new Explosive;
	for (int i = 0; i < 4; i++)
		M.tow[i]->pos = { g->square[20][16 + 2 * i].pos.x + H_SQUARE_SIZE, g->square[20][16 + 2 * i].pos.y + H_SQUARE_SIZE };
	M.hasSelected = false;
}

// returns 1 if tower needs to be placed
int Menu::update()
{
	if (this->mMenu == Type_Menu::IN_GAME) {
		if (!M.hasSelected && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			for (int i = 0; i < 4; i++)
				if (M.hasSelected == false && M.tow[i]->isMouseOverTower()) {
					M.selection = *M.tow[i];
					M.hasSelected = true;
				}
		if (M.hasSelected && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			ImVec2 mouse = ImGui::GetMousePos();
			M.selection.setPos(mouse.x, mouse.y);
		}
		if (M.hasSelected && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
			M.hasSelected = false;
			return 1;
		}
	}
	return 0;
}

void Menu::draw(Grid *g)
{
	ImDrawList* dl = ImGui::GetBackgroundDrawList();
	switch (this->mMenu)
	{
	case Type_Menu::LOADING:
		dl->AddRectFilled({ 0,0 }, { WIDTH,HEIGHT }, BLACK);
		dl->AddText(this->font, 60, { WIDTH/2-100,HEIGHT/2-50 }, WHITE, "LOADING...");
		break;
	case Type_Menu::MAIN:
		break;
	case Type_Menu::IN_GAME:
		dl->AddRectFilled({ g->square[20][16].pos.x, g->square[20][16].pos.y },
			{ g->square[21][23].pos.x + SQUARE_SIZE, g->square[21][23].pos.y + SQUARE_SIZE },
			WHITE, 5.f); // background square
		for (int i = 0; i < 4; i++) {
			M.tow[i]->draw(0);
			dl->AddText(this->font, 16, { g->square[21][16 + 2 * i].pos.x + 2.f, g->square[21][16 + 2 * i].pos.y }, BLACK, M.tow[i]->getTypeName());
			char price[20];
			sprintf(price, "-%d c", M.tow[i]->price);
			dl->AddText(this->font, 16,  { g->square[21][16 + 2 * i].pos.x + 2.f, g->square[21][16 + 2 * i].pos.y + H_SQUARE_SIZE }, BLACK, price);
		}
		if (M.hasSelected)
			M.selection.draw();
		break;
	case Type_Menu::PAUSE:
		break;
	case Type_Menu::VICTORY:
		break;
	case Type_Menu::LOSE:
		break;
	case Type_Menu::QUIT:
		break;

	case Type_Menu::NONE:
	default:
		break;
	}
}