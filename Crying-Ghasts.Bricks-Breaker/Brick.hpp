#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "GameObject.hpp"

namespace sf {
	class RenderWindow;
}

class Brick : public GameObject
{
private:
	int maxHealth;
	int health;

public:
	Brick(sf::Vector2f _position, int _maxHealth = 1);
	~Brick();

	int MaxHealth() { return maxHealth; }
	int Health() { return health; }
	bool isAlive() { return health > 0; }

	Brick* setHealth(int _maxHealth);
	void updateBrickColor();

	void Update(float dT) override;
	void Render(sf::RenderWindow* window) override;

	bool TakeDamage(int amount);

	void OnCollisionEnter(GameObject* collider) override;
};