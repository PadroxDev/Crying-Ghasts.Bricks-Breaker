#pragma once

#include <iostream>
#include <string>

using namespace std;
using namespace sf;


namespace sf 
{
	class RenderWindow;
	class Clock;
}

class App
{
private:
	RenderWindow* window;
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
