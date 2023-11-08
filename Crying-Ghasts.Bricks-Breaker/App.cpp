#include <SFML/Graphics.hpp>
#include <iostream>
#include "App.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Mathematics.hpp"

using namespace std;
using namespace sf;

const unsigned int FRAME_CAP = 200;

GameObject* Bullet;
GameObject* Cannon;
GameObject* Brick;

App::App(int width, int height) {
	InitWindow(width, height);

    Bullet = new GameObject(Vector2f(1280 / 2 - 200, 300), Vector2f(100, 100), sf::Color::Red, Vector2f(-1, 0) * 150.0f, ShapeType::Circle);
    Cannon = new GameObject(Vector2f(1280 / 2 - 100, 550), Vector2f(200, 200), sf::Color::Blue, Vector2f(0,0), ShapeType::Triangle);
    Brick = new GameObject(Vector2f(200 / 2, 300), Vector2f(75, 75), sf::Color::Black, Vector2f(0, 0), ShapeType::Circle);

    InputManager::Initialize();
}

App::~App()
{
    delete Bullet, Cannon, Brick;
}

void App::InitWindow(int width, int height) {
    window = new RenderWindow(VideoMode(width, height), "Crying Ghasts", Style::Default);
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
    sf::Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
        }
    }
}

void App::Update() {
    deltaTime = clock->restart();
    float dTs = deltaTime.asSeconds();

    Bullet->Update(dTs);
    Cannon->Update(dTs);
    Brick->Update(dTs);

    if (InputManager::Instance->isMouseDown()) {
        cout << "Button pressed !";
    }

    Vector2i pos = InputManager::Instance->mousePosition(*window);

    Brick->SetPosition(Vector2f(pos.x, pos.y));

    Mathematics::Collision_AABB_Circle(Bullet->Position(), Cannon->Size(), Cannon->Position(), (Cannon->Size().x + Cannon->Size().y) * 0.25f);

    if (Bullet->CollidesWith(Brick)) {
        Bullet->SetVelocity(Bullet->Velocity() * -1.f);
    }
}

void App::Render() {
    window->clear(Color::White);

    RectangleShape boundingShape1 = RectangleShape(Vector2f(Bullet->Size()));
    RectangleShape boundingShape2 = RectangleShape(Vector2f(Brick->Size()));

    boundingShape1.setFillColor(sf::Color::Green);
    boundingShape2.setFillColor(sf::Color::Green);

    boundingShape1.setPosition(Bullet->Position());
    boundingShape2.setPosition(Brick->Position());

    window->draw(boundingShape1);
    window->draw(boundingShape2);

    Bullet->Render(window);
    Cannon->Render(window);
    Brick->Render(window);

    window->display();
}