#pragma once

// C Includes
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

// Own Includes
#include "GameObject.hpp"

#ifndef SAVELOAD_HPP
#define SAVELOAD_HPP

extern void DeleteObject(std::unique_ptr<GameObject>& toErase, std::vector<std::unique_ptr<GameObject>> &objects);

extern void DeleteObjects(std::vector<std::unique_ptr<GameObject>> &objs, std::vector<std::unique_ptr<GameObject>> &objects);

extern bool SaveObjects(std::string path, std::string filename, std::vector<std::unique_ptr<GameObject>> &list);

extern bool LoadObjects(std::string path, std::string filename, std::vector<std::unique_ptr<GameObject>> &list);

#endif SAVELOAD_HPP