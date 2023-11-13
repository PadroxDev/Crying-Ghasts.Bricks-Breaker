#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cannon.hpp"
#include "InputManager.hpp"
#include "Mathematics.hpp"
#include "Bullet.hpp"

Cannon::Cannon(sf::Vector2f _pos, std::vector<GameObject*>* _gameObjectsList)
	: GameObject(_pos, sf::Vector2f(150, 150), ShapeType::Triangle, sf::Color::Blue)
{
	gameObjectsList = _gameObjectsList;
}

Cannon::~Cannon()
{}

void Cannon::Update(float dT) {
	Shoot();
}

void Cannon::Render(sf::RenderWindow* window) {
	mousePos = InputManager::Instance->mousePosition(*window);
	GameObject::Render(window);
}

void Cannon::Shoot() {
	if (!InputManager::Instance->isMouseDown()) {
		mouseDown = false;
		return;
	}

	if (mouseDown) return;
	mouseDown = true;

	std::cout << "SHOOT" << std::endl;

	sf::Vector2f dir = sf::Vector2f(mousePos.x, mousePos.y) - position;
	Mathematics::Normalize(&dir);

	sf::Vector2f spawnPos = position + dir * 100.0f;

	Bullet* bullet = new Bullet(spawnPos, dir);
	gameObjectsList->push_back(bullet);
}