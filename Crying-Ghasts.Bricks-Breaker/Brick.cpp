#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "App.hpp"
#include "Brick.hpp"
#include "Mathematics.hpp"

std::map<int, sf::Color> HealthColorStates{
	{0, sf::Color(255, 16, 240)},
	{1, sf::Color(224, 89, 52)},
	{2, sf::Color(224, 135, 52)},
	{3, sf::Color(224, 189, 74)},
	{4, sf::Color(74, 166, 70)},
	{5, sf::Color(35, 156, 217)}
};

Brick::Brick(sf::Vector2f _position, int _maxHealth) : GameObject(_position,
	sf::Vector2f(100, 40), ShapeType::Rectangle, sf::Color::Black)
{
	maxHealth = _maxHealth;
	health = maxHealth;
	updateBrickColor();
}

Brick::~Brick()
{}

Brick* Brick::setHealth(int _health) {
	health = _health;
	return this;
}

void Brick::Update(float dT) {
	GameObject::Update(dT);
}

void Brick::Render(sf::RenderWindow* window) {
	GameObject::Render(window);
}

bool Brick::TakeDamage(int amount) {
	health = Mathematics::Clamp(health - amount, 0, maxHealth);
	updateBrickColor();
	if (isAlive()) return false;
	ToDestroy = true;
	return true;
}

void Brick::OnCollisionEnter(GameObject* collider) {
	TakeDamage(1);
}

void Brick::updateBrickColor() {
	setColor(HealthColorStates[health]);
}