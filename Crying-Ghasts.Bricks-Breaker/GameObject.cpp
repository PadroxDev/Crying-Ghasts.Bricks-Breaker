#include <algorithm>
#include <iostream>
#include "GameObject.hpp"
#include "Mathematics.hpp"

using namespace sf;
using namespace std;

GameObject::GameObject(Vector2f _position, Vector2f _size, sf::Color _color, Vector2f dir, ShapeType _type) :
	position(_position), size(_size), color(_color), velocity(dir), shapeType(_type), anchors(Vector2f(1, 1) * 0.5f)
{
	SetShape(shapeType);
	SetAnchors(anchors);
	shape->setFillColor(color);
}

GameObject::~GameObject()
{}

void GameObject::SetPosition(Vector2f _position)
{
	position = _position;
	shape->setPosition(position + Vector2f(size.x * anchors.x, size.y * anchors.y));
}

float getRadiusFromSize(Vector2f size) {
	return (size.x + size.y) * 0.25f;
}

void GameObject::SetSize(Vector2f _size)
{
	size = _size; // Retrieve shape size because size is updated as well ?
	Vector2f scaleFactor = Vector2f(_size.x / size.x, _size.y / size.y);
	shape->setScale(scaleFactor);
}

void GameObject::SetAnchors(Vector2f _anchors)
{ 
	anchors = _anchors;
	Vector2f origin = Vector2f(size.x * anchors.x, size.y * anchors.y);
	shape->setOrigin(origin);
}

void GameObject::SetRotationAngle(float rotAngle)
{
	rotationAngle = rotAngle;
	shape->setRotation(rotationAngle);
}

void GameObject::SetColor(sf::Color _color)
{
	color = _color;
	shape->setFillColor(color);
}

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

void GameObject::MoveAlongVelocity(float dT)
{
	if (velocity == Vector2f(0, 0)) return;
	position += velocity * dT;
}

void GameObject::Update(float dT) {
	MoveAlongVelocity(dT);
}

void GameObject::Render(RenderWindow* window) {
	Shape* boundingBox;
	if (shapeType == Rectangle) {
		boundingBox = new RectangleShape(size);
	}
	else {
		boundingBox = new CircleShape((size.x + size.y) * 0.25f);
	}
	boundingBox->setScale(shape->getScale());
	boundingBox->setPosition(position);
	boundingBox->setOrigin(shape->getOrigin());
	boundingBox->setFillColor(sf::Color::Green);
	boundingBox->setRotation(rotationAngle);

	shape->setPosition(position);
	shape->setRotation(rotationAngle);
	window->draw(*boundingBox);
	window->draw(*shape);
	delete boundingBox;
}

bool GameObject::CollidesWith(GameObject* go) {
	const auto collidingIndex = std::find(collidingGameObjects.begin(),
		collidingGameObjects.end(), go);

	bool collide = false;
	switch (shapeType) {
	case Rectangle:
		collide = Mathematics::Collision_AABB_AABB(position, size, go->Position(), go->Size());
		break;
	case Circle:
		collide = Mathematics::Collision_Circle_Circle(position, size.x * 0.5f, go->position, go->size.x * 0.5f);
		break;
	}

	if (collide) {
		if (collidingIndex != collidingGameObjects.end()) {
			OnCollisionStay(go);
		}
		else {
			collidingGameObjects.push_back(go);
			OnCollisionEnter(go);
		}
		return true;
	}

	if (collidingIndex != collidingGameObjects.end()) {
		collidingGameObjects.erase(collidingIndex);
		OnCollisionExit(go);
	}
	return false;
}

void GameObject::OnCollisionEnter(GameObject* collider) {
	std::cout << "OnCollisionEnter" << std::endl;
}

void GameObject::OnCollisionStay(GameObject* collider) {}

void GameObject::OnCollisionExit(GameObject* collider) {
	std::cout << "OnCollisionExit" << std::endl;
}