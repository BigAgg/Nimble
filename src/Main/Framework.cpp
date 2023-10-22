#include "Framework.hpp"

Vector2* mpGame, * mpMenu;

Framework::Framework(std::string name)
{
	LoadSettings();

	// Initializing Window
	InitWindow(1, 1, name.c_str());
	// Initializing Audio device
	InitAudioDevice();
	SetExitKey(KEY_NULL);

	// Setting up Window Settings
	SetupWindow(this->width, this->height, this->fps, this->fullscreen, this->borderless, this->vsync);
}

Framework::~Framework()
{
	SaveSettings();
	CloseAudioDevice();
	CloseWindow();
}

void Framework::SetupWindow(int width, int height, int fps, bool fullscreen, bool borderless, bool vsync)
{
	// Setting up Window Settings
	this->width = width;
	this->height = height;
	this->fps = fps;
	this->fullscreen = fullscreen;
	this->borderless = borderless;
	this->vsync = vsync;

	int cmw = GetMonitorWidth(GetCurrentMonitor());		// Current Monitor Width
	int cmh = GetMonitorHeight(GetCurrentMonitor());	// Current Monitor Height

	if (width > cmw)
		width = cmw;
	if (height > cmh)
		height = cmh;

	// Getting through Window Settings
	if (GetFPS() != fps)
		SetTargetFPS(fps);
	ClearWindowState(FLAG_WINDOW_UNDECORATED);
	ClearWindowState(FLAG_VSYNC_HINT);

	// Setting Vsync
	if (vsync)
		SetWindowState(FLAG_VSYNC_HINT);

	// Making Window ready for Fullscreen
	if (fullscreen || borderless)
	{
		width = cmw;
		height = cmh;
		SetWindowPosition(0, 0);
	}

	// Placing Window in right Position for Fullscreen
	else if (height == cmh)
	{
		if (!fullscreen)
		{
			//this->borderless = true;
			borderless = true;
		}
		if (!borderless)
		{
			//this->fullscreen = true;
			fullscreen = true;
		}
		SetWindowPosition(0, 0);
	}

	// Placing Window in middle of Screen
	else if (!fullscreen)
	{
		ClearWindowState(FLAG_FULLSCREEN_MODE);
		SetWindowPosition(cmw / 2 - width / 2, cmh / 2 - height / 2);
	}

	SetWindowSize(width, height);

	// Toggle fullscreen
	if (fullscreen != IsWindowFullscreen())
	{
		ToggleFullscreen();
	}

	if (borderless)
		SetWindowState(FLAG_WINDOW_UNDECORATED);

	// Setting up Cameras
	menuCam.offset = Vector2{ 0, 0 };
	menuCam.rotation = 0.0f;
	menuCam.zoom = (float)width / 1920;
	menuCam.target = Vector2{ 0, 0 };
	gameCam.offset = Vector2{ (float)width / 2, (float)height / 2 };
	gameCam.rotation = 0.0f;
	gameCam.zoom = (float)width / 1920;
	gameCam.target = Vector2{ 0, 0 };

	SaveSettings();
}

void Framework::SetupAudio(float mainVolume, float musicVolume)
{
	this->mainVolume = mainVolume;
	this->musicVolume = musicVolume;
	SetMasterVolume(mainVolume);
	/*
	* Will be done in the future when music is being loaded in
	* SetMusicVolume(currentMusic, musicVolume);
	*/
}

void Framework::SetTarget(Vector2 target)
{
	gameCam.target = target;
}

void Framework::SaveSettings()
{
	using namespace std;
	namespace fs = filesystem;

	fs::create_directories("bin/");

	ofstream file;
	file.open("bin/window.stg", ios::binary);
	if (file.is_open() && file.good())
	{
		file.write((char*)this, sizeof(Framework));
	}
	file.close();
}

void Framework::LoadSettings()
{
	using namespace std;

	ifstream file;
	file.open("bin/window.stg", ios::binary);
	if (file.is_open() && file.good())
	{
		file.read((char*)this, sizeof(Framework));
	}
	else
	{
		width = 1920;
		height = 1080;
		fullscreen = false;
		vsync = false;
		fps = 60;
	}
	file.close();
}

void Framework::BeginMode(int mode)
{
	switch (mode)
	{
	case 0:
		BeginMode2D(gameCam);
		break;
	case 1:
		BeginMode2D(menuCam);
		break;
	default:
		BeginMode2D(gameCam);
		break;
	}
}

void Framework::Update()
{
	*mpMenu = GetScreenToWorld2D(GetMousePosition(), menuCam);
	*mpGame = GetScreenToWorld2D(GetMousePosition(), gameCam);

	float mouseScroll = GetMouseWheelMove();
	if (mouseScroll)
	{
		gameCam.zoom += mouseScroll;
		float minscroll = (float)width / 1920;
		float maxscroll = 6.0f * width / 1920;
		if (gameCam.zoom > maxscroll)
			gameCam.zoom = maxscroll;
		else if (gameCam.zoom < minscroll)
			gameCam.zoom = minscroll;
	}
}
