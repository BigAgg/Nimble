#include "Globals.hpp"

Framework *fw;

int gameState = 0;

Vector2 mousePosMenu;
Vector2 mousePosGame;

void SetGamestate(int newGamestate)
{
	gameState = newGamestate;
	switch (gameState)
	{
	case MENU:
		SetMenuState(MAIN_MENU);
		break;
		
	case GAMING:
		SetMenuState(GAMING_UI);
		break;

	case LEVEL_EDITOR:
		break;

	case TEXTURE_EDITOR:
		break;
	}
}

int keybinds[] = { KEY_W, KEY_S, KEY_A, KEY_D, KEY_F, KEY_Q, KEY_E, KEY_Y, KEY_C, KEY_SPACE,
					KEY_TAB, KEY_ONE, KEY_TWO, KEY_FOUR, KEY_R, KEY_LEFT_CONTROL, KEY_F10, KEY_F9 };
char keybindsChar[] = { 'w', 's', 'a', 'd', 'f', 'q', 'e', 'y', 'c', ' ', ' ', '1', '2', '3', '4', 'r', ' ', ' '};
void SaveKeybinds()
{
	using namespace std;
	namespace fs = filesystem;

	fs::create_directories("bin/");

	ofstream file;
	file.open("bin/keybinds.kbs", ios::binary);
	if (file.is_open() && file.good())
	{
		file.write((char*)&keybinds, sizeof(keybinds));
		file.write((char*)&keybindsChar, sizeof(keybindsChar));
	}
	file.close();
}

void LoadKeybinds()
{
	using namespace std;

	ifstream file;
	file.open("bin/keybinds.kbs", ios::binary);
	if (file.is_open() && file.good())
	{
		file.read((char*)&keybinds, sizeof(keybinds));
		file.read((char*)&keybindsChar, sizeof(keybindsChar));
	}
}

void SetMenuState(int newMenustate)
{
	if (gameState != MENU && newMenustate == MAIN_MENU)
		newMenustate = INGAME_MENU;
	else if (gameState == MENU && newMenustate == INGAME_MENU)
		newMenustate = MAIN_MENU;
	drawMenus[newMenustate] = true;
}

void ToggleMenuState(int menuState)
{
	drawMenus[menuState] = !drawMenus[menuState];
}

void ClearMenuState(int menustate)
{
	drawMenus[menustate] = false;
}

void ClearAllMenuStates()
{
	for (bool& x : drawMenus)
		x = false;
}