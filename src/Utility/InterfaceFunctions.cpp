#ifndef INTERFACEFUNCTIONS_CPP
#define INTERFACEFUNCTIONS_CPP

#include "InterfaceFunctions.hpp"

void QuitGame()
{
	SetGamestate(CLOSE_GAME);
}

void OpenSettings()
{
	SetMenuState(SETTINGS_MENU);
	ClearMenuState(MAIN_MENU);
	ClearMenuState(INGAME_MENU);
}

void OpenLoadMenu()
{
	SetMenuState(LOAD_MENU);
	ClearMenuState(MAIN_MENU);
	ClearMenuState(INGAME_MENU);
}

void OpenSaveMenu() 
{
	SetMenuState(SAVE_MENU);
	ClearMenuState(INGAME_MENU);
}

void ChangeResolution()
{
	int width = fw->width;
	int height = fw->height;
	int fps = fw->fps;
	bool fullscreen = fw->fullscreen;
	bool borderless = fw->borderless;
	bool vsync = fw->vsync;
	switch (width)
	{
	case 1280:
		width = 1920;
		height = 1080;
		break;
	case 1920:
		width = 2560;
		height = 1440;
		break;
	case 2560:
		width = 3840;
		height = 2160;
		break;
	default:
		width = 1280;
		height = 720;
		break;
	}
	fw->SetupWindow(width, height, fps, fullscreen, borderless, vsync);
}

void SetBorderless()
{
	fw->borderless = !fw->borderless;
	if (fw->borderless && fw->fullscreen)
		fw->fullscreen = !fw->fullscreen;
	fw->SetupWindow(fw->width, fw->height, fw->fps, fw->fullscreen, fw->borderless, fw->vsync);
}

void SetFullscreen()
{
	fw->fullscreen = !fw->fullscreen;
	if (fw->fullscreen && fw->borderless)
		fw->borderless = !fw->borderless;
	fw->SetupWindow(fw->width, fw->height, fw->fps, fw->fullscreen, fw->borderless, fw->vsync);
}

void SetFPS()
{
	if (fw->vsync)
	{
		int refreshRate = GetMonitorRefreshRate(GetCurrentMonitor());
		fw->fps = refreshRate;
		SetTargetFPS(refreshRate);
		return;
	}
	SetTargetFPS(fw->fps);
}

void AsignKeybind(int keyID, int key, char charKey)
{
	ResetKeybinders();
	int idx = 0;
	for (auto &x : keybinds)
	{
		if (x == key)
		{
			x = 0;
			keybindsChar[idx] = '*';
		}
		idx++;
	}
	keybindsChar[keyID] = charKey;
	keybinds[keyID] = key;
	for (auto &&x : menus[KEYBINDS_MENU])
	{
		if (x->name != "Back")
		{
			x->update();
		}
	}
}

void ResetKeybinders()
{
	for (auto &&x : menus[KEYBINDS_MENU])
	{
		if (x->name != "Back")
		{
			Keybinder& tmp = (Keybinder&)x;
			tmp.waitForKey = false;
		}
	}
}

#endif INTERFACEFUNCTIONS_CPP