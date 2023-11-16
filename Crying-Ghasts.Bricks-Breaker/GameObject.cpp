#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.hpp"
#include "Mathematics.hpp"

using namespace sf;
using namespace std;

GameObject::GameObject(Vector2f _position, Vector2f _size, ShapeType _type, sf::Color _color)
{
	setShape(_type)->setPosition(_position, sf::Vector2f(0.5f, 0.5f))->setSize(_size)
		->setColor(_color);
	canCollide = true;
	ToDestroy = false;
}

GameObject::GameObject(Vector2f _position, Vector2f _size, Vector2f _velocity, ShapeType _type, sf::Color _color) :
	GameObject(_position, _size, _type, _color)
{
	setVelocity(_velocity);
}

GameObject::~GameObject()
{}

Vector2f GameObject::GetPosition(sf::Vector2f anchors) {
	return Vector2f(position.x + size.x * anchors.x, position.y + size.y * anchors.y);
}

GameObject* GameObject::setPosition(Vector2f _position, sf::Vector2f anchors)
{
	position = _position;
	Vector2f relativePosition = _position + sf::Vector2f(size.x * anchors.x, size.y * anchors.y);

	shape->setPosition(relativePosition);
	return this;
}

GameObject* GameObject::setSize(Vector2f _size)
{
	size = _size;

	// Scale is relative to the default size of 1000
	Vector2f defaultSize(1000, 1000);
	Vector2f relativeScale = Vector2f(size.x / defaultSize.x, size.y / defaultSize.y);
	shape->setScale(relativeScale);
	return this;
}

GameObject* GameObject::setVelocity(Vector2f _velocity) {
	velocity = _velocity;
	return this;
}

GameObject* GameObject::setRotationAngle(float rotAngle, sf::Vector2f anchors)
{
	rotationAngle = rotAngle;
	shape->setOrigin(Vector2f(1000 * anchors.x, 1000 * anchors.y));
	shape->setRotation(rotationAngle);
	return this;
}

GameObject* GameObject::setShape(ShapeType type){
	switch (type) {
	case(ShapeType::Rectangle):
		shape = new RectangleShape(Vector2f(1000, 1000));
		break;
	case(ShapeType::Triangle):
		shape = new CircleShape(500, 3);
		break;
	case(ShapeType::Circle):
		shape = new CircleShape(500);
		break;
	};
	return this;
}

GameObject* GameObject::setColor(sf::Color _color)
{
	color = _color;
	shape->setFillColor(color);
	return this;
}

GameObject* GameObject::setCanCollide(bool can) {
	canCollide = can;
	return this;
}

void GameObject::Move(float dT)
{
	if (velocity == Vector2f(0, 0)) return;
	setPosition(position + velocity * dT, sf::Vector2f(0,0));
}

void GameObject::Update(float dT)
{
	Move(dT);
}

void GameObject::DisplayBoundingBox(RenderWindow* window) {
	Shape* boundingBox;
	if (shapeType == ShapeType::Rectangle) {
		boundingBox = new RectangleShape(Vector2f(1000, 1000));
	}
	else {
		boundingBox = new CircleShape(500);
	}
	boundingBox->setScale(shape->getScale());
	boundingBox->setPosition(position);
	boundingBox->setFillColor(sf::Color::Green);

	window->draw(*boundingBox);
	delete boundingBox;
}

void GameObject::Render(RenderWindow* window) {
	//DisplayBoundingBox(window);
	window->draw(*shape);
}

bool GameObject::CollidesWith(GameObject* go) {
	if (!canCollide || !go->canCollide) return false;
	const auto collidingIndex = std::find(collidingGameObjects.begin(),
		collidingGameObjects.end(), go);

	bool collide = false;
	switch (shapeType) {
	case Rectangle:
		collide = Mathematics::Collision_AABB_AABB(position, size, go->GetPosition(), go->Size());
		break;
	case Circle:
		collide = Mathematics::Collision_Circle_Circle(position, size.x * 0.5f, go->GetPosition(), go->size.x * 0.5f);
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

void GameObject::OnCollisionEnter(GameObject* collider)
{}

void GameObject::OnCollisionStay(GameObject* collider) 
{}

void GameObject::OnCollisionExit(GameObject* collider)
{}