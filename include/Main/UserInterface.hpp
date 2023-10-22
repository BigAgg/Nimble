#pragma once
// C Includes
#include <string>
#include <functional>
#include <memory>

// Raylib Includes
#include "raylib.h"

// Own Includes
#include "InterfaceFunctions.hpp"

#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

//\return Base Button Module
class module
{
public:
	module(Rectangle rect, int textSize, std::string name, Texture2D texture = { 0,0,0,0,0 });
	virtual ~module();

	//\return Checks if the module is pressed and returns a bool
	virtual bool IsPressed(Vector2 mousePos);
	//\return Checks if the mouse is hovering over the module and returns a bool
	bool IsHovered(Vector2 mousePos);
	//\return Updates the module and calls its given function
	virtual void update();
	//\return Draws the module
	virtual void draw();
	//\return Asigns given void function to variable func
	void AsignFunc(std::function<void()> func);

	std::string name, content;
	Texture2D texture;
	int textSize;
	Vector2 textPos = { 0.0f, 0.0f };
	Rectangle rect;
	std::function<void()> func;
	bool funcSet = false;
};

class ValueModule : public module
{
public:
	ValueModule(Rectangle rect, int textSize, std::string name, Texture2D texture = { 0,0,0,0,0 }, int* val = nullptr, int* val2 = nullptr);
	~ValueModule();
	void update();
	int* val;
	int* val2;
};

//\return Slider, Parent: module, Used to access variables via pointers ingame
class Slider : public module
{
public:
	Slider(Rectangle rect, int textSize, std::string name, Texture2D texture = {0,0,0,0,0});
	~Slider();

	//\return Sets either a int pointer or a float pointer to this slider
	void SetPointer(int* ival=nullptr, float* fval=nullptr);
	//\return Sets either int or float min and max values for 
	void SetBounds(int imin=0, int imax=0, float fmin=0.0f, float fmax=0.0f);

	bool IsPressed(Vector2 mousePos);
	void update();
	void draw();

	Vector2 sliderPos;
	Rectangle sliderRect;
	Texture2D sliderTexture;
	float sliderSize = 4.0f;
	bool isSlid = false;
	int imin, imax;
	float fmin, fmax;
	int* ival;
	float* fval;
};

class Keybinder : public module
{
public:
	Keybinder(int keyID, Rectangle rect, int textSize, std::string name, Texture2D texture = { 0,0,0,0,0 });
	~Keybinder();

	bool IsPressed(Vector2 mp);
	void update();

	int keyID;
	bool waitForKey = false;
};

const int totalMenus = 18;

extern std::vector<std::unique_ptr<module>> menus[totalMenus];
extern bool drawMenus[totalMenus];

extern void UpdateMenus();
extern void DrawMenus();

extern void SetupMenus();

extern Vector2* mp;
extern Font f;

#endif USERINTERFACE_HPP