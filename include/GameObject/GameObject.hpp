#pragma once
// C Includes
#include <vector>
#include <string>
#include <memory>

// Raylib Includes
#include "raylib.h"

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

class GameObject
{
public:
	// Creates GameObject and adds itself to the objects vector
	GameObject(Vector2 position, Rectangle cropbox, Rectangle hitbox, uint16_t layer, uint16_t textureID[3]);
	~GameObject();

	// Base Operations
	bool operator==(const GameObject* right) const;
	bool operator<(const GameObject* right) const;

	// Setting up GameObject type string
	void SetType(std::string type);
	// Setting up given Texture2D
	void SetTexture(Texture2D texture);
	
	// Handles Keyboard inputs
	virtual void input();
	// Updates GameObject
	virtual void update();
	// Draws GameObject to Screen
	virtual void draw();

	std::string type = "GameObject";
	Vector2 pos, offset;
	Rectangle hitbox, cropbox;
	Texture2D texture;
	uint16_t layer;
	uint16_t textureID[3];
	uint64_t id;
};

//\return Struct to sort GameObject in a Vector
struct less_than_key
{
	inline bool operator() (std::unique_ptr<GameObject>& objl, std::unique_ptr<GameObject>& objr)
	{
		return (objl.get()->id < objr.get()->id);
	}
};

//TODO: When Chunks and Scenes are implemented, get rid of objects and have a Vector in each scene and each Chunk
//\return Vector that stores all GameObjects
extern std::vector<std::unique_ptr<GameObject>> objects;

//TODO: Since hitbox==pos, might delete pos in Future as it is not needed
//\return Updates the Cropbox and the Hitbox
extern void UpdateObjectRecs(GameObject* obj);

#endif GAMEOBJECT_HPP