#include <SFML/Graphics.hpp>
#include "InputManager.hpp"

using namespace sf;

InputManager* InputManager::Instance = nullptr;

InputManager::InputManager()
{}

InputManager::~InputManager()
{
	delete InputManager::Instance;
}

void InputManager::Initialize() {
	if (InputManager::Instance != nullptr)
		return;

	InputManager::Instance = new InputManager();
}

bool InputManager::isMouseDown() {
	return Mouse::isButtonPressed(Mouse::Left);
}

Vector2i InputManager::mousePosition(const WindowBase& window) {
	return Mouse::getPosition(window);
}