#pragma once

#include <iostream>
#include <string>

namespace sf 
{
	class RenderWindow;
	class Clock;
}

class App
{
private:
	sf::RenderWindow* window;
	sf::Clock* clock;
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
