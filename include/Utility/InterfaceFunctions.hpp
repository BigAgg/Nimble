#pragma once

#ifndef INTERFACEFUNCTIONS_HPP
#define INTERFACEFUNCTIONS_HPP
// Own Includes
#include "Globals.hpp"

extern void QuitGame();
extern void OpenSettings();
extern void OpenLoadMenu();
extern void ChangeResolution();
extern void SetBorderless();
extern void SetFullscreen();
extern void SetFPS();
extern void AsignKeybind(int keyID, int key, char charKey);
extern void ResetKeybinders();

#endif INTERFACEFUNCTIONS_HPP