#pragma once

#include <SFML/System/Vector2.hpp>
#include "GameObject.hpp"

class Brick : public GameObject
{
private:
	int hp;

public:
	Brick(sf::Vector2f _position, int _hp);
	~Brick();

	Brick* setHp(int _hp); 
	bool isAlive();

	void Update(float dT) override;
	void Render(sf::RenderWindow* window) override;
};