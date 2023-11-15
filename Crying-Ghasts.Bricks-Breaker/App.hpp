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
class Brick;

static class App
{
private:
	static App* instance;

	sf::RenderWindow* window;
	sf::Clock* clock;
	sf::Time deltaTime;
	std::vector<GameObject*> gameObjects;
	sf::Vector2i gridSize;

	App(int width, int height);

public:
	static void Initialize();
	static App* GetInstance() { return instance; }
	~App();

	sf::RenderWindow* GetWindow() { return window; }
	sf::Time DeltaTime() { return deltaTime; }

	void InitWindow(int width, int height);
	void Loop();
	void HandleEvents();
	void Update();
	void Render();

	void GenerateBrickGrid();

	void RemoveGameObject(GameObject* brick);
};
