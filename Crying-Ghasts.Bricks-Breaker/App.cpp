#include <SFML/Graphics.hpp>
#include <iostream>
#include "App.hpp"
#include "Cannon.hpp"
#include "GameObject.hpp"
#include "Bullet.hpp"
#include "InputManager.hpp"
#include "Mathematics.hpp"

using namespace std;
using namespace sf;

const unsigned int FRAME_CAP = 200;

App::App(int width, int height) {
	InitWindow(width, height);
    gameObjects.push_back(
        new Cannon(Vector2f(1280 * 0.5f, 600), &gameObjects));
    gameObjects.push_back(
        new GameObject(Vector2f(1280 * 0.5f, 190), Vector2f(150, 60), ShapeType::Rectangle, sf::Color(139, 69, 19)));
    GameObject* LineUp = new GameObject(Vector2f(0, 0), Vector2f(window->getSize().x, 10), ShapeType::Rectangle, sf::Color::Blue);
    LineUp->setAnchors(Vector2f(0, 0));
    GameObject* LineLeft = new GameObject(Vector2f(0, 0), Vector2f(10, window->getSize().y), ShapeType::Rectangle, sf::Color::Blue);
    LineLeft->setAnchors(Vector2f(0, 0));
	GameObject* LineRight = new GameObject(Vector2f(window->getSize().x, 0), Vector2f(10, window->getSize().y), ShapeType::Rectangle, sf::Color::Blue);
	LineRight->setAnchors(Vector2f(1, 0));
    GameObject* LineDown = new GameObject(Vector2f(0, window->getSize().y), Vector2f(window->getSize().x, 10), ShapeType::Rectangle, sf::Color::Blue);
    LineDown->setAnchors(Vector2f(0, 1));
    gameObjects.push_back(LineUp);
    gameObjects.push_back(LineLeft);
    gameObjects.push_back(LineRight);
    gameObjects.push_back(LineDown);
    InputManager::Initialize();
}

App::~App()
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        delete gameObjects[i];
    }
}

void App::InitWindow(int width, int height) {
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new RenderWindow(VideoMode(width, height), "Crying Ghasts", Style::Default, settings);
    window->setFramerateLimit(FRAME_CAP);
    clock = new Clock();
}

void App::Loop() {
    while (window->isOpen()) {
        HandleEvents();
        Update();
        Render();
    }
}

void App::HandleEvents() {
    Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
        case Event::Closed:
            window->close();
        }
    }
}

void App::Update() {
    deltaTime = clock->restart();
    float dT = deltaTime.asSeconds();

    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Update(dT);
        for (int j = 0; j < gameObjects.size(); j++)
        {
            if (j == i) continue;
            gameObjects[i]->CollidesWith(gameObjects[j]);
        }
    }
}

void App::Render() {
    window->clear(Color::White);

    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Render(window);
    }

    window->display();
}