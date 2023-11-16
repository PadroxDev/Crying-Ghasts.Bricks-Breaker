#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cannon.hpp"
#include "InputManager.hpp"
#include "Mathematics.hpp"
#include "Bullet.hpp"

Cannon::Cannon(sf::Vector2f _pos, std::vector<GameObject*>* _gameObjectsList)
	: GameObject(_pos, sf::Vector2f(150, 90), ShapeType::Rectangle, sf::Color::Blue)
{
	gameObjectsList = _gameObjectsList;
	setPosition(_pos, sf::Vector2f(0.5f, 0.5f));
	canCollide = false;
}

Cannon::~Cannon()
{}

void Cannon::Update(float dT) {
	sf::Vector2f dir = sf::Vector2f(mousePos.x, mousePos.y) - GetPosition(sf::Vector2f(0.5f, 0.5f));
	Mathematics::Normalize(&dir);

	float angle = Mathematics::AngleFromDirection(dir) * Mathematics::RAD2DEG;
	setRotationAngle(Mathematics::Clamp(angle, -45-90, 45-90));

	Shoot();
}

void Cannon::Render(sf::RenderWindow* window) {
	mousePos = InputManager::GetInstance()->mousePosition(*window);

	shape->setPosition(position + size * 0.5f);
	window->draw(*shape);
}

void Cannon::Shoot() {
	if (!InputManager::GetInstance()->isMouseDown()) {
		mouseDown = false;
		return;
	}

	if (mouseDown || existingBullets >= 3) return;
	mouseDown = true;

	sf::Vector2f dir = sf::Vector2f(mousePos.x, mousePos.y) - GetPosition(sf::Vector2f(0.5f, 0.5f));
	Mathematics::Normalize(&dir);

	sf::Vector2f spawnPos = GetPosition(sf::Vector2f(0.5f, 0.5f)) + dir * 150.0f;

	Bullet* bullet = new Bullet(spawnPos, dir, &existingBullets);
	gameObjectsList->push_back(bullet);
	existingBullets++;
}