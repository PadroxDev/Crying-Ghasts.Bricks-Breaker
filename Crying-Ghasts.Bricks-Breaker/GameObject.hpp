#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>

enum ShapeType{
	Rectangle,
	Triangle,
	Circle
};

namespace sf {
	class RenderWindow;
	class Shape;
}

class GameObject
{
protected:
	sf::Vector2f position;
	sf::Vector2f relativePosition;
	sf::Vector2f size;
	sf::Vector2f anchors;
	sf::Vector2f velocity;
	float rotationAngle;
	sf::Shape* shape;
	ShapeType shapeType;
	sf::Color color;
	std::vector<GameObject*> collidingGameObjects;

public:
	GameObject(sf::Vector2f _position, sf::Vector2f _size, ShapeType _type, sf::Color _color);
	GameObject(sf::Vector2f _position, sf::Vector2f _size, sf::Vector2f _velocity, ShapeType type, sf::Color _color);
	~GameObject();

	sf::Vector2f Position() { return position; }
	sf::Vector2f RelativePos() { return relativePosition; }
	sf::Vector2f Size() { return size; }
	sf::Vector2f Anchors() { return anchors; }
	sf::Vector2f Velocity() { return velocity; }
	float RotationAngle() { return rotationAngle; }
	sf::Color Color() { return color; }

	// Chaining methods
	GameObject* setPosition(sf::Vector2f _position);
	GameObject* setSize(sf::Vector2f _size);
	GameObject* setAnchors(sf::Vector2f _anchors);
	GameObject* setVelocity(sf::Vector2f _velocity);
	GameObject* setRotationAngle(float rotAngle);
	GameObject* setShape(ShapeType type);
	GameObject* setColor(sf::Color _color);

	void UpdateRelativePosition();
	
	virtual void Update(float dT);
	
	void DisplayBoundingBox(sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);

	void Move(float dT);

	bool CollidesWith(GameObject* go);
	virtual void OnCollisionEnter(GameObject* collider);
	virtual void OnCollisionStay(GameObject* collider);
	virtual void OnCollisionExit(GameObject* collider);
};