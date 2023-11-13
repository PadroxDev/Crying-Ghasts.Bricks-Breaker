#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.hpp"
#include "Mathematics.hpp"

Bullet::Bullet(sf::Vector2f _position, sf::Vector2f _direction, float _speed) : GameObject(
	_position, sf::Vector2f(30, 30), ShapeType::Circle, sf::Color::Red)
{
	setDirection(_direction)->setSpeed(_speed);
}

Bullet::~Bullet()
{}

Bullet* Bullet::setDirection(sf::Vector2f _dir) {
	dir = _dir;
	UpdateVelocity();
	return this;
}

Bullet* Bullet::setSpeed(float _speed) {
	speed = _speed;
	UpdateVelocity();
	return this;
}

void Bullet::UpdateVelocity() {
	setVelocity(dir * speed);
}

void Bullet::Update(float dT) {
	GameObject::Update(dT);
}

void Bullet::Render(sf::RenderWindow* window) {
	GameObject::Render(window);
}

void Bullet::OnCollisionEnter(GameObject* collider) {
	sf::Vector2f normalVector = Mathematics::GetNormalOfCollision(this, collider);
	sf::Vector2f reflectDir = Mathematics::Reflect(normalVector, dir);
	setDirection(reflectDir);
}