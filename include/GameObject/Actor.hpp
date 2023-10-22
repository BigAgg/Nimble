#pragma once
// Own Includes
#include "GameObject.hpp"
#include <functional>

#ifndef ACTOR_HPP
#define ACTOR_HPP

class Actor :
    public GameObject
{
public:
    Actor(Vector2 position, Rectangle cropbox, Rectangle hitbox, uint16_t layer, uint16_t textureID[3]);
    ~Actor();

    void SetBehavior(int behaveID);
    void SetInput(int inputID);
    void kill();
    void SetStats(int intelligence, int strength, int agility, int crit);
    void SetResistences(int armor, int magicResist, int block, int fireResist, int frostResist, int arcaneResist);

    void input();
    void update();
    void draw();

    Vector2 dir;
    Vector2 target;
    Vector2 path[60];
    bool isAlive;
    int health, mana, stamina, speed;
    struct Stats 
    {
        int intelligence = 0;
        int strength = 0;
        int agility = 0;
        int crit = 0;
    };
    struct Resistances 
    {
        int armor = 0;
        int magicResist = 0;
        int block = 0;
        int fireResist = 0;
        int frostResist = 0;
        int arcaneResist = 0;
    };
    int behaveID = -1;
    int inputID = -1;
private:
    void (*behaviorFunc)(Actor);
    void (*inputFunc)(Actor);
};

#endif ACTOR_HPP