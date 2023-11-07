#include <algorithm>
#include <iostream>
#include "GameObject.hpp"

using namespace sf;
using namespace std;

GameObject::GameObject(Vector2f _position, Vector2f _size, sf::Color _color, Vector2f dir, ShapeType _type) :
	position(_position), size(_size), color(_color), velocity(dir), type(_type)
{
	SetShape(type);
	shape->setFillColor(color);
}

GameObject::~GameObject()
{}

void GameObject::SetShape(ShapeType type){
	switch (type) {
	case(ShapeType::Rectangle):
		shape = new RectangleShape(size);
		break;
	case(ShapeType::Triangle):
		shape = new CircleShape((size.x + size.y)*0.25f, 3);
		break;
	case(ShapeType::Circle):
		shape = new CircleShape((size.x + size.y) * 0.25f);
		break;
	};
}

void GameObject::Update(float dT) {
	if (velocity == Vector2f(0, 0)) return;
	position += velocity * dT;
}

void GameObject::Render(RenderWindow* window) {
	shape->setPosition(position);
	window->draw(*shape);
}

bool GameObject::CollidesWith(const GameObject* go) {
	return !((go->position.x >= position.x + size.x)
		|| (go->position.x + go->size.x <= position.x)
		|| (go->position.y >= position.y + size.y)
		|| (go->position.y + go->size.y <= position.y));
}