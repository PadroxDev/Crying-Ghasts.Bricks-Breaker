#pragma once

#include <SFML/System/Vector2.hpp>

namespace sf 
{
	class WindowBase;
}

class InputManager
{
private:
	static InputManager* instance;
	InputManager();

public:
	~InputManager();

	static InputManager* GetInstance() { return instance; }

	static void Initialize();

	bool isMouseDown();
	sf::Vector2i mousePosition(const sf::WindowBase& window);
};