#pragma once

// C Includes
#include <vector>
#include <memory>

// Raylib Includes
#include "raylib.h"

// Own Includes
#include "GameObject.hpp"
#include "Debug.hpp"
#include "UserInterface.hpp"
#include "Actor.hpp"

namespace assetseditor {
	extern void loop();
	extern void input();
	extern void update();
	extern void draw();
}