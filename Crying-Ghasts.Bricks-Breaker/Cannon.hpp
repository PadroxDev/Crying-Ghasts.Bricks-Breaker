#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "GameObject.hpp"

namespace sf {
	class RenderWindow;
}

class Cannon : public GameObject
{
private:
	sf::Vector2i mousePos = sf::Vector2i(0, 0);
	std::vector<GameObject*>* gameObjectsList;
	bool mouseDown = false;

public:
	Cannon(sf::Vector2f _pos, std::vector<GameObject*>* gameObjectsList);
	~Cannon();

	void Update(float dT) override;
	void Render(sf::RenderWindow* window) override;

	void Shoot();
};