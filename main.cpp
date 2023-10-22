// Common includes
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>


// Raylib includes
#include "raylib.h"

// Own includes
#include "UserInterface.hpp"
#include "Globals.hpp"
#include "Debug.hpp"
#include "GameObject.hpp"
#include "SaveLoad.hpp"
#include "AssetsEditor.hpp"

// Declaring base Variables
Rectangle clippingRect = {0, 0, 1920, 1080};
Rectangle chunkloader = {-1920, -1080, 5760, 3240};

/*void* operator new(size_t size)
{
	std::cout << "Allocating " << size << " bytes\n";

	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	std::cout << "Freeing " << size << " bytes\n";

	free(memory);
}*/

void gameinput()
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		SetMenuState(INGAME_MENU);
	}
}

void input()
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		SetGamestate(MENU);
		ClearAllMenuStates();
		SetMenuState(MAIN_MENU);
	}
}

void handleUI()
{
	UpdateMenus();
}

void drawGame()
{
	BeginDrawing();
	ClearBackground(DARKGRAY);

	// Drawing Game
	fw->BeginMode(0);
	// Draw stuff
	for (auto &&obj : objects)
	{
		if (CheckCollisionRecs(obj->cropbox, clippingRect))
			debugobj(obj.get(), 2);
	}
	EndMode2D();

	// Drawing User Interface
	fw->BeginMode(1);
	// Draw menu

	EndMode2D();

	DrawFPS(0, 0);
	EndDrawing();
}

void drawMenu()
{
	BeginDrawing();
	ClearBackground(DARKGRAY);

	fw->BeginMode(1);

	DrawMenus();

	EndMode2D();
	DrawFPS(0, 0);
	EndDrawing();
}

void game()
{
	gameinput();
	handleUI();
	drawGame();
}

void menu()
{
	input();
	handleUI();
	drawMenu();
}

int main(int argc, char** argv[])
{
	fw = new Framework("Nimble RPG");
	LoadKeybinds();
	SetupMenus();
	SetGamestate(MENU);
	mpMenu = &mousePosMenu;
	mpGame = &mousePosGame;
	mp = &mousePosMenu;
	f = LoadFont("SDS_8x8.ttf");

	while (gameState != CLOSE_GAME)
	{
		fw->Update();
		switch (gameState)
		{
		case GAMING:
			game();
			break;
			
		case MENU:
			menu();
			break;

		case LEVEL_EDITOR:
			SetGamestate(MENU);
			ClearAllMenuStates();
			SetMenuState(MAIN_MENU);
			break;

		case TEXTURE_EDITOR:
			SetGamestate(MENU);
			ClearAllMenuStates();
			SetMenuState(MAIN_MENU);
			break;

		default:
			SetGamestate(MENU);
			ClearAllMenuStates();
			SetMenuState(MAIN_MENU);
			break;
		}
		if (WindowShouldClose())
			SetGamestate(CLOSE_GAME);
	}
	for (auto&& x : menus)
	{
		for (auto&& y : x)
		{
			y.release();
		}
		x.clear();
	}
	menus->clear();
	for (auto&& x : objects)
	{
		x.release();
	}
	SaveKeybinds();
	delete fw;
}