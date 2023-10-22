#include "Actor.hpp"

Actor::Actor(Vector2 position, Rectangle cropbox, Rectangle hitbox, uint16_t layer, uint16_t textureID[3])
: GameObject(position, cropbox, hitbox, layer, textureID)
{
	SetType("Actor");
}

Actor::~Actor() {

}

void Actor::SetBehavior(int behaveID)
{
}

void Actor::SetInput(int inputID)
{
}

void Actor::kill()
{
}

void Actor::SetStats(int intelligence, int strength, int agility, int crit)
{
}

void Actor::SetResistences(int armor, int magicResist, int block, int fireResist, int frostResist, int arcaneResist)
{
}

void Actor::input()
{
}

void Actor::update()
{
}

void Actor::draw()
{
}

