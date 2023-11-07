#include <algorithm>
#include <iostream>
#include "GameObject.hpp"
#include "Mathematics.hpp"

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
	return (!Mathematics::Collision_AABB_AABB(position, size,
		go->position, go->size));
}

bool GameObject::CollidesWith(const GameObject* go, Collision* outCollision) {
	if (!CollidesWith(go)) return false;
	
	outCollision->collider = go;

	sf::Vector2f centerThis = position + size * .5f;
	sf::Vector2f centerGO = go->position + go->size * .5f;
	sf::Vector2f centerDiff = centerGO - centerThis;
	sf::Vector2f minDist = (size + go->size) * 0.5f - sf::Vector2f(std::abs(centerDiff.x), std::abs(centerDiff.y));

	if (minDist.x < minDist.y) {
		outCollision->normal = sf::Vector2f(std::signbit(centerDiff.x) ? -1.0f : 1.0f, 0.0f);
	}
	else {
		outCollision->normal = sf::Vector2f(0.0f, std::signbit(centerDiff.y) ? -1.0f : 1.0f);
	}

	return true;
}