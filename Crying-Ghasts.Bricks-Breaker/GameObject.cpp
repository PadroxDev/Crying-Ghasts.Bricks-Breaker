#include "GameObject.hpp"

GameObject::GameObject(Vector2f _position, Vector2f _size, Shape* _shape, Color _color, Vector2f dir) :
	position(_position), size(_size), shape(_shape), color(_color), Direction(dir)
{
	shape->setFillColor(color);
}

GameObject::~GameObject()
{}

void GameObject::Update(float dT) {
	position += Direction * dT;
}

void GameObject::Render(RenderWindow* window) {
	shape->setPosition(position);
	shape->setScale(size);
	window->draw(*shape);
}

bool GameObject::CollidesWith(const GameObject* go) {
	return !(go->position.x >= position.x + size.x)
		|| (go->position.x + go->size.x <= position.x
		|| (go->position.y >= position.y + size.y)
		|| (go->position.y + go->size.y <= position.y));
}