#include "Debug.hpp"

void debug(std::string any, Vector2 position, int fontSize, Color color)
{
	DrawText(any.c_str(), int(position.x), int(position.y), fontSize, color);
}

void debugobj(GameObject* obj, int mode)
{
	switch (mode)
	{
	case 0:
		DrawRectangleRec(obj->cropbox, PURPLE);
		break;
	case 1:
		DrawRectangleLinesEx(obj->hitbox, 1.0f, RED);
		break;
	case 2:
		debugobj(obj, 0);
		debugobj(obj, 1);
		break;
	}
}
