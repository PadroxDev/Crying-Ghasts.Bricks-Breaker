#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject
{
private:
	Vector2f position;
	Vector2f size;
	Shape* shape;
	Color color;

public:
	Vector2f Direction;

	GameObject(Vector2f _position, Vector2f _size, Shape* _shape, Color _color, Vector2f dir);
	~GameObject();

	virtual void Update(float dT);

	virtual void Render(RenderWindow* window);

	bool CollidesWith(const GameObject* go);
};