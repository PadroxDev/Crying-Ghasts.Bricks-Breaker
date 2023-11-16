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
	sf::Vector2f size;
	sf::Vector2f velocity;
	float rotationAngle;
	sf::Shape* shape;
	ShapeType shapeType;
	sf::Color color;
	bool canCollide;
	std::vector<GameObject*> collidingGameObjects;

public:
	bool ToDestroy;

	GameObject(sf::Vector2f _position, sf::Vector2f _size, ShapeType _type, sf::Color _color);
	GameObject(sf::Vector2f _position, sf::Vector2f _size, sf::Vector2f _velocity, ShapeType type, sf::Color _color);
	virtual ~GameObject();

	sf::Vector2f GetPosition(sf::Vector2f anchors = sf::Vector2f(0,0));
	sf::Vector2f Size() { return size; }
	sf::Vector2f Velocity() { return velocity; }
	float RotationAngle() { return rotationAngle; }
	sf::Color Color() { return color; }

	// Chaining methods
	GameObject* setPosition(sf::Vector2f _position, sf::Vector2f anchors = sf::Vector2f(0,0));
	GameObject* setSize(sf::Vector2f _size);
	GameObject* setVelocity(sf::Vector2f _velocity);
	GameObject* setRotationAngle(float rotAngle, sf::Vector2f anchors = sf::Vector2f(0.5, 0.5));
	GameObject* setShape(ShapeType type);
	GameObject* setColor(sf::Color _color);
	GameObject* setCanCollide(bool can);
	
	virtual void Update(float dT);
	
	void DisplayBoundingBox(sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);

	void Move(float dT);

	bool CollidesWith(GameObject* go);
	virtual void OnCollisionEnter(GameObject* collider);
	virtual void OnCollisionStay(GameObject* collider);
	virtual void OnCollisionExit(GameObject* collider);
};