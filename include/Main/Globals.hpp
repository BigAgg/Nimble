#pragma once

// C Includes
#include <vector>

// Raylib Includes
#include "raylib.h"

// Own Includes
#include "Framework.hpp"
#include "UserInterface.hpp"

#ifndef GLOBALS_HPP
#define GLOBALS_HPP

extern Framework *fw;

// Game-State handling
enum gs
{
	MENU = 0,
	GAMING = 1,
	LEVEL_EDITOR = 2,
	TEXTURE_EDITOR = 3,
	CLOSE_GAME = 100
};
extern int gameState;
extern void SetGamestate(int newGamestate);

// Keybinds
enum kb
{
	WALK_FORWARD = 0,
	WALK_BACKWARDS = 1,
	WALK_LEFT = 2,
	WALK_RIGHT = 3,
	INTERACT = 4,
	SPELL_1 = 5,
	SPELL_2 = 6,
	SPELL_3 = 7,
	SPELL_4 = 8,
	SPECIAL = 9,
	OPEN_INVENTORY = 10,
	USE_ITEM_1 = 11,
	USE_ITEM_2 = 12,
	USE_ITEM_3 = 13,
	USE_ITEM_4 = 14,
	CHARGE = 15,
	QUICKSAVE = 16,
	QUICKLOAD = 17
};
const int possibleKeys[] = {
	KEY_TAB,
	KEY_LEFT_SHIFT,
	KEY_LEFT_ALT,
	KEY_LEFT_CONTROL,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_SPACE
};
const int totalKeys = 18;
extern int keybinds[totalKeys];
extern char keybindsChar[totalKeys];
//\return Saves current Keybinds to "bin/keybinds.kbs"
extern void SaveKeybinds();
//\return Loads Keybinds from "bin/keybinds.kbs"
extern void LoadKeybinds();

// Menu-State handling
enum ms {
	MAIN_MENU = 0,
	SETTINGS_MENU = 1,
	GRAPHICS_MENU = 2,
	SOUND_MENU = 3,
	KEYBINDS_MENU = 4,
	LOAD_MENU = 5,
	SAVE_MENU = 6,
	NEWGAME_MENU = 7,
	GAMING_UI = 8,
	PLAYER_INVENTORY_UI = 9,
	TARGET_INVENTORY_UI = 10,
	SMITHING_UI = 11,
	LEATHERWORKING_UI = 12,
	CLOTHIER_UI = 13,
	ENCHANTER_UI = 14,
	ALCHEMIST_UI = 15,
	DEATHSCREEN_MENU = 16,
	INGAME_MENU = 17,
};
extern void SetMenuState(int newMenustate);
extern void ToggleMenuState(int menuState);
extern void ClearMenuState(int menustate);
extern void ClearAllMenuStates();

// Global Mouse Positions
extern Vector2 mousePosMenu;
extern Vector2 mousePosGame;

#endif GLOBALS_HPP