#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cannon.hpp"
#include "InputManager.hpp"
#include "Mathematics.hpp"
#include "Bullet.hpp"

Cannon::Cannon(sf::Vector2f _pos, std::vector<GameObject*>* _gameObjectsList)
	: GameObject(_pos, sf::Vector2f(150, 150), ShapeType::Rectangle, sf::Color::Blue)
{
	gameObjectsList = _gameObjectsList;
	canCollide = false;
	shape->setOrigin(500, 500);
}

Cannon::~Cannon()
{}

void Cannon::Update(float dT) {
	sf::Vector2f dir = sf::Vector2f(mousePos.x, mousePos.y) - position + sf::Vector2f(500, 500);
	Mathematics::Normalize(&dir);

	float angle = Mathematics::AngleFromDirection(dir) * Mathematics::RAD2DEG;
	setRotationAngle(angle);

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

	if (mouseDown) return;
	mouseDown = true;

	sf::Vector2f dir = sf::Vector2f(mousePos.x, mousePos.y) - position;
	Mathematics::Normalize(&dir);

	sf::Vector2f spawnPos = position + dir * 150.0f;

	Bullet* bullet = new Bullet(spawnPos, dir);
	gameObjectsList->push_back(bullet);
}