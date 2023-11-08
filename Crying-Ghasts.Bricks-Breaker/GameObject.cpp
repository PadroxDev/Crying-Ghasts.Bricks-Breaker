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
	shape->setPosition(position);
}

float getRadiusFromSize(Vector2f size) {
	return (size.x + size.y) * 0.25f;
}

void GameObject::SetSize(Vector2f _size)
{
	size = _size;
	//switch (shapeType) {
	//case ShapeType::Rectangle:
	//	{
	//		RectangleShape* rectangleShape = dynamic_cast<RectangleShape*>(shape);
	//		rectangleShape->setSize(size);
	//	}
	//case Triangle:
	//	{
	//		CircleShape* triangleShape = dynamic_cast<CircleShape*>(shape);
	//		triangleShape->setRadius(getRadiusFromSize(size));
	//	}
	//case Circle:
	//	{
	//		CircleShape* circleShape = dynamic_cast<CircleShape*>(shape);
	//		circleShape->setRadius(getRadiusFromSize(size));
	//	}
	//}
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
	shape->setRotation(rotationAngle);
	window->draw(*shape);
}

bool GameObject::CollidesWith(const GameObject* go) {
	return (!Mathematics::Collision_AABB_AABB(position, size,
		go->position, go->size));
}

bool GameObject::CollidesWith(const GameObject* go, Collision* outCollision) {
	if (!CollidesWith(go)) return false;
	
	outCollision->collider = go;

	Vector2f centerThis = position + size * .5f;
	Vector2f centerGO = go->position + go->size * .5f;
	Vector2f centerDiff = centerGO - centerThis;
	Vector2f minDist = (size + go->size) * 0.5f - Vector2f(std::abs(centerDiff.x), std::abs(centerDiff.y));

	if (minDist.x < minDist.y) {
		outCollision->normal = Vector2f(std::signbit(centerDiff.x) ? -1.0f : 1.0f, 0.0f);
	}
	else {
		outCollision->normal = Vector2f(0.0f, std::signbit(centerDiff.y) ? -1.0f : 1.0f);
	}

	return true;
}