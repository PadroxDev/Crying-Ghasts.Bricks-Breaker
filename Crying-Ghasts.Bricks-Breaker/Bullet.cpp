#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.hpp"
#include "Mathematics.hpp"
#include "App.hpp"

Bullet::Bullet(sf::Vector2f _position, sf::Vector2f _direction, int* _existingBullets, float _speed) : GameObject(
	_position, sf::Vector2f(30, 30), ShapeType::Eyeball, sf::Color::White), existingBullets(_existingBullets)
{
	setDirection(_direction)->setSpeed(_speed);
}

Bullet::~Bullet()
{
	*existingBullets -= 1;
}

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

	sf::RenderWindow* window = App::GetInstance()->GetWindow();
	sf::Vector2u windowSize = window->getSize();
	if (position.x < -40
		|| position.x > windowSize.x + 40
		|| position.y < -40
		|| position.y > windowSize.y + 40)
	{
		// Out of window bounds
		ToDestroy = true;
	}
}

sf::Vertex line[2];

void Bullet::Render(sf::RenderWindow* window) {
	GameObject::Render(window);
	window->draw(line, 4, sf::Lines);
}

void Bullet::OnCollisionEnter(GameObject* collider) {
	GetSideToCollide(collider);
}

void Bullet::UpdateDirection(int side) {
	switch (side) {
	case 0: // Top collision
		setDirection(sf::Vector2f(dir.x, -std::abs(dir.y)));
		break;
	case 1: // Bottom collision
		setDirection(sf::Vector2f(dir.x, std::abs(dir.y)));
		break;
	case 2: // Left collision
		setDirection(sf::Vector2f(-std::abs(dir.x), dir.y));
		break;
	case 3: // Right collision
		setDirection(sf::Vector2f(std::abs(dir.x), dir.y));
		break;
	}
}

void Bullet::MultiplyDirection(float _factorX, float _factorY)
{
	dir.x *= _factorX;
	dir.y *= _factorY;
}

void Bullet::ResolveCollision(const GameObject* entity, int side) {
	float overlap = 5.0f;

	switch (side) {
	case 0: // Top collision
		UpdateDirection(side);
		break;
	case 1: // Bottom collision
		UpdateDirection(side);
		break;
	case 2: // Left collision
		UpdateDirection(side);
		break;
	case 3: // Right collision
		UpdateDirection(side);
		break;
	}
}

int Bullet::GetSideToCollide(GameObject* entity) {
	float ball_bottom = position.y + size.y;
	float brick_bottom = entity->GetPosition().y + entity->Size().y;
	float ball_right = position.x + size.x;
	float brick_right = entity->GetPosition().x + entity->Size().x;

	float y_overlap = std::min(ball_bottom, brick_bottom) - std::max(position.y, entity->GetPosition().y);
	float x_overlap = std::min(ball_right, brick_right) - std::max(position.x, entity->GetPosition().x);

	float minOverlapThreshold = 5.0f;

	if (y_overlap > x_overlap && y_overlap > minOverlapThreshold) {
		if (position.x < entity->GetPosition().x) {
			// Left collision
			ResolveCollision(entity, 2);
			return 2;
		}
		else {
			// Right collision
			ResolveCollision(entity, 3);
			return 3;
		}
	}
	else if (x_overlap > minOverlapThreshold) {
		if (position.y < entity->GetPosition().y) {
			// Top collision
			ResolveCollision(entity, 0);
			return 0;
		}
		else {
			// Bottom collision
			ResolveCollision(entity, 1);
			return 1;
		}
	}

	return -1; // No collision
}