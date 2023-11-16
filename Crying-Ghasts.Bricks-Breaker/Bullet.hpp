#pragma once

#include <SFML/System/Vector2.hpp>
#include "GameObject.hpp"
#include "Cannon.hpp"

namespace sf {
	class RenderWindow;
}

class Bullet : public GameObject
{
private:
	sf::Vector2f dir;
	float speed;
	int* existingBullets;

public:
	Bullet(sf::Vector2f _position, sf::Vector2f _direction, int* _existingBullets, float _speed = 350);
	~Bullet() override;

	Bullet* setDirection(sf::Vector2f _direction);
	Bullet* setSpeed(float _speed);
	void UpdateVelocity();

	void Update(float dT) override;
	void Render(sf::RenderWindow* window) override;

	void OnCollisionEnter(GameObject* collider) override;

	void MultiplyDirection(float _factorX, float _factorY);
	void UpdateDirection(int side);
	void ResolveCollision(const GameObject* entity, int side);
	int GetSideToCollide(GameObject* entity);
};