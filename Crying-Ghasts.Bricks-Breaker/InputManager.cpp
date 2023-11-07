//#include <SFML/Graphics.hpp>
//#include "InputManager.hpp"
//
//using namespace sf;
//
//InputManager::InputManager()
//{}
//
//InputManager::~InputManager()
//{
//	delete Instance;
//}
//
//void InputManager::Initialize() {
//	if (Instance != nullptr)
//		return;
//
//	Instance = new InputManager();
//}
//
//bool InputManager::MouseDown() {
//	return Mouse::isButtonPressed(Mouse::Left);
//}