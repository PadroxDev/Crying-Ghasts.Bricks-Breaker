#pragma once

#include <SFML/Graphics.hpp>
#include <map>

enum ShapeType{
	Rectangle,
	Triangle,
	Circle
};

class GameObject;

class GameObject
{
private:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f anchors;
	float rotationAngle;
	sf::Vector2f velocity;
	sf::Shape* shape;
	ShapeType shapeType;
	sf::Color color;
	std::vector<GameObject*> collidingGameObjects;

public:
	GameObject(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, sf::Vector2f dir, ShapeType _type);
	~GameObject();

	sf::Vector2f Position() { return position; }
	sf::Vector2f Size() { return size; }
	sf::Vector2f Anchors() { return anchors; }
	float RotationAngle() { return rotationAngle; }
	sf::Vector2f Velocity() { return velocity; }
	sf::Color Color() { return color; }

	void SetPosition(sf::Vector2f _position);
	void SetSize(sf::Vector2f _size);
	void SetAnchors(sf::Vector2f _anchors);
	void SetRotationAngle(float rotAngle);
	void SetVelocity(sf::Vector2f _velocity) { velocity = _velocity; };
	void SetColor(sf::Color _color);
	virtual void SetShape(ShapeType type);

	void MoveAlongVelocity(float dT);

	virtual void Update(float dT);
	virtual void Render(sf::RenderWindow* window);

	bool CollidesWith(GameObject* go);
	virtual void OnCollisionEnter(GameObject* collider);
	virtual void OnCollisionStay(GameObject* collider);
	virtual void OnCollisionExit(GameObject* collider);
};