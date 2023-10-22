#include "raylib.h"
#include <string>
#include "GameObject.hpp"
#include <chrono>
#include <iostream>

#ifndef DEBUG_HPP
#define DEBUG_HPP

//\return Drawing a given String on given Position with given Size and Color
extern void debug(std::string any, Vector2 position, int fontSize = 10, Color color = GREEN);
// \return Drawing Rectangles of given obj depending on the mode
// 0 Drawing Cropbox
// 1 Drawing Hitbox
// 2 Drawing both
extern void debugobj(GameObject* obj, int mode=0);

class Timer
{
public:
	Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		Stop();
	}
	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;
		std::cout << "Duration: " << duration << "us (" << ms << "ms)\n";
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};

#endif DEBUG_HPP