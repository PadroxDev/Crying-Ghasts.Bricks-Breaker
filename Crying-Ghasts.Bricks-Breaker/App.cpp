#include <SFML/Graphics.hpp>
#include <iostream>
#include "App.hpp"
#include "Cannon.hpp"
#include "Brick.hpp"
#include "Bullet.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Mathematics.hpp"

using namespace std;
using namespace sf;

const unsigned int FRAME_CAP = 200;
const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

App* App::instance = nullptr;

App::App(int width, int height) : gridSize(Vector2i(7, 5)) {
	InitWindow(width, height);
    gameObjects.push_back(new Cannon(Vector2f(1280 * 0.5f, 650), &gameObjects));
    GameObject* LineUp = new GameObject(Vector2f(0, 0), Vector2f(window->getSize().x, 20), ShapeType::Rectangle, sf::Color::Blue);
    GameObject* LineLeft = new GameObject(Vector2f(0, 0), Vector2f(20, window->getSize().y), ShapeType::Rectangle, sf::Color::Blue);
	GameObject* LineRight = new GameObject(Vector2f(window->getSize().x-20, 0), Vector2f(20, window->getSize().y), ShapeType::Rectangle, sf::Color::Blue);
    gameObjects.push_back(LineUp);
    gameObjects.push_back(LineLeft);
    gameObjects.push_back(LineRight);

    std::srand(time(0));
    GenerateBrickGrid();
}

App::~App()
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        delete gameObjects[i];
    }

    delete instance;
}

void App::Initialize() {
    if (App::instance != nullptr) return;

    App::instance = new App(WINDOW_WIDTH, WINDOW_HEIGHT);
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
        case Event::MouseButtonPressed:
            break;
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

    for (int i = gameObjects.size()-1; i >= 0 ; i--)
    {
        GameObject* go = gameObjects[i];
        if (go->ToDestroy) {
            gameObjects.erase(gameObjects.begin() + i);
            delete go;
        }
    }
}

void App::Render() {
    window->clear(Color::Black);

    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Render(window);
    }

    window->display();
}

void App::GenerateBrickGrid() {
    for (int i = 0; i < gridSize.x; i++)
    {
        for (int j = 0; j < gridSize.y; j++)
        {
            Vector2f size(100, 40);
            Vector2f padding(7, 7);
            Vector2f pos = Vector2f(240, 150) + Vector2f(size.x * i, size.y * j) + Vector2f(padding.x * i, padding.y * j);
            GameObject* brick = new Brick(pos, rand() % 5 + 1);
            gameObjects.push_back(brick);
        }
    }
}

//bool App::CheckWin() {
//    int count;
//    for (int i = 0; i < gameObjects.size(); ++i) 
//    {
//        GameObject* objPtr = gameObjects[i];
//        if (dynamic_cast<Brick*>(objPtr) != nullptr) 
//        {
//            count++;
//        }
//    }
//    return count == 0;
//}


//void App::WinScreen() {
//    window->clear(Color::Black);
//    for (int i = 0; i < gameObjects.size(); i++)
//    {
//        delete gameObjects[i];
//    }
//    sf::Texture winTexture = Texture();
//    winTexture.loadFromFile("res/images/win.png");
//    GameObject* textureVessel = new GameObject(sf::Vector2f(0, 90), sf::Vector2f(1280,540), ShapeType::Rectangle, sf::Color::White);
//    textureVessel->setTexture(&winTexture);
//    textureVessel->Render(window);
//}