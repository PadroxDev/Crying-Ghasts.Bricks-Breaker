#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace sf 
{
	class RenderWindow;
	class Clock;
}

class GameObject;

class App
{
private:
	sf::RenderWindow* window;
	sf::Clock* clock;
	sf::Time deltaTime;
	std::vector<GameObject*> gameObjects;

public:
	App(int width, int height);
	~App();

	sf::Time DeltaTime() { return deltaTime; }

	void InitWindow(int width, int height);
	void Loop();
	void HandleEvents();
	void Update();
	void Render();

	void GenerateBrickGrid();
};
