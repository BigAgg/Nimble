#include "GameObject.hpp"

std::vector<std::unique_ptr<GameObject>> objects;

void UpdateObjectRecs(GameObject* obj)
{
	obj->cropbox.x = obj->pos.x + obj->offset.x;
	obj->cropbox.y = obj->pos.y + obj->offset.y;
	obj->hitbox.x = obj->pos.x;
	obj->hitbox.y = obj->pos.y;
}

GameObject::GameObject(Vector2 position, Rectangle cropbox, Rectangle hitbox, uint16_t layer, uint16_t textureID[3])
{
	pos = position;
	this->offset = { cropbox.x - hitbox.x, cropbox.y - hitbox.y };
	this->hitbox = hitbox;
	this->cropbox = cropbox;
	UpdateObjectRecs(this);
	this->layer = layer;
	for (int x = 0; x < 3; x++)
	{
		this->textureID[x] = textureID[x];
	}
	this->id = objects.size();
	objects.emplace_back(this);
}

GameObject::~GameObject()
{
}

bool GameObject::operator==(const GameObject* right) const
{
	return (this->id == right->id);
}

bool GameObject::operator<(const GameObject* right) const
{
	return (this->id < right->id);
}

void GameObject::SetType(std::string type){
	this->type = type;
}

void GameObject::SetTexture(Texture2D texture) {
	this->texture = texture;
}

void GameObject::input(){

}

void GameObject::update(){

}

void GameObject::draw(){
	if (texture.id)
	{
		DrawTextureV(texture, { cropbox.x, cropbox.y }, WHITE);
	}
}
