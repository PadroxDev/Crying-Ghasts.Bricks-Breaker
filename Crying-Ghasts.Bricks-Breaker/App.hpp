#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class App
{
private:
	Window* window;
	Clock* clock;
	sf::Time deltaTime;

public:
	App(int width, int height);
	~App();

	sf::Time DeltaTime() { return deltaTime; }

	void InitWindow(int width, int height);
	void Loop();
	void HandleEvents();
	void Update();
	void Render();
};
