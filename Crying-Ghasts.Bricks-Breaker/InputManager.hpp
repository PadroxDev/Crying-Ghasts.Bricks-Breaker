#pragma once

#include <SFML/System/Vector2.hpp>

namespace sf 
{
	class WindowBase;
}

static class InputManager
{
private:
	InputManager();

public:
	static InputManager* Instance;
	~InputManager();

	static InputManager* GetInstance() { return Instance; }

	static void Initialize();

	bool isMouseDown();
	sf::Vector2i mousePosition(const sf::WindowBase& window);

	//void operator=(const InputManager&) = delete;
};