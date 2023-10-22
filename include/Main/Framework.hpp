#pragma once

// C Includes
#include <string>
#include <filesystem>
#include <fstream>

// Raylib Includes
#include "raylib.h"

#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

extern Vector2* mpGame, * mpMenu;

//\return Main Framework to handle Window related stuff such as rescaling, Cameras and Mouse Positions
class Framework
{
public:
	Framework(std::string name);
	~Framework();

	//\return Setting up main Window, also saving given settings
	void SetupWindow(int width, int height, int fps = 60, bool fullscreen = false, bool borderless = false, bool vsync = false);
	//\return Setting up Adio device and loading in music
	void SetupAudio(float mainVolume, float musicVolume);
	//\return Sets the gameCam target to given Vector2
	void SetTarget(Vector2 target);

	//\return Saves Window settings to "bin/window.stg" file
	void SaveSettings();
	//\return Loads Window settings from "bin/window.stg" file
	void LoadSettings();

	//\return Calls BeginMode2D with given mode: 0=gameCam 1=menuCam default=gameCam
	void BeginMode(int mode);
	//\return Updates Framework related stuff
	void Update();

	int width, height, fps;
	float mainVolume, musicVolume;
	bool fullscreen, borderless, vsync;
private:
	Camera2D gameCam, menuCam;
};

#endif FRAMEWORK_HPP