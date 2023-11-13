#pragma once

#include <SFML/System/Vector2.hpp>
#include "GameObject.hpp"

namespace sf {
	class RenderWindow;
}

class Bullet : public GameObject
{
private:
	sf::Vector2f dir;
	float speed;

public:
	Bullet(sf::Vector2f _position, sf::Vector2f _direction, float _speed = 350);
	~Bullet();

	Bullet* setDirection(sf::Vector2f _direction);
	Bullet* setSpeed(float _speed);
	void UpdateVelocity();

	void Update(float dT) override;
	void Render(sf::RenderWindow* window) override;

	void OnCollisionEnter(GameObject* collider) override;
};