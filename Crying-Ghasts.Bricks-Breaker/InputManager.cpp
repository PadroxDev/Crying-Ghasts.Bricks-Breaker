#include <SFML/Graphics.hpp>
#include "InputManager.hpp"

using namespace sf;

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{}

InputManager::~InputManager()
{
	delete InputManager::instance;
}

void InputManager::Initialize() {
	if (InputManager::instance != nullptr)
		return;

	InputManager::instance = new InputManager();
}

bool InputManager::isMouseDown() {
	return Mouse::isButtonPressed(Mouse::Left);
}

Vector2i InputManager::mousePosition(const WindowBase& window) {
	return Mouse::getPosition(window);
}