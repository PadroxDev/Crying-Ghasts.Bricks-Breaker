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
GameObject* Koko;
GameObject* Kiki;
GameObject* BIG_BALL;
GameObject* LineUp;
GameObject* LineLeft;
GameObject* LineRight;
GameObject* LineDown;

App::App(int width, int height) {
	InitWindow(width, height);

    Bullet = new GameObject(Vector2f(1280 / 2 - 200, 300), Vector2f(100, 100), sf::Color::Red, Vector2f(0.1, -1) * 150.0f, ShapeType::Rectangle);
    Cannon = new GameObject(Vector2f(1280 / 2 - 100, 550), Vector2f(200, 200), sf::Color::Blue, Vector2f(0,0), ShapeType::Triangle);
    Brick = new GameObject(Vector2f(200 / 2, 300), Vector2f(75, 75), sf::Color::Black, Vector2f(0, 0), ShapeType::Circle);
    Koko = new GameObject(Vector2f(0, 0), Vector2f(100, 100), sf::Color::Cyan, Vector2f(0, 0), ShapeType::Rectangle);
    Kiki = new GameObject(Vector2f(800, 400), Vector2f(150, 150), sf::Color::Magenta, Vector2f(0, 0), ShapeType::Rectangle);
    BIG_BALL = new GameObject(Vector2f(500, 400), Vector2f(100, 100), sf::Color::Yellow, Vector2f(0, 0), ShapeType::Rectangle);
    LineUp = new GameObject(Vector2f(0, 0), Vector2f(window->getSize().x, 5), sf::Color::Blue, Vector2f(0, 0), ShapeType::Rectangle);
    LineUp->SetAnchors(Vector2f(0, 0));
    LineLeft = new GameObject(Vector2f(0, 0), Vector2f(5, window->getSize().y), sf::Color::Blue, Vector2f(0, 0), ShapeType::Rectangle);
    LineLeft->SetAnchors(Vector2f(0, 0));
	LineRight = new GameObject(Vector2f(window->getSize().x, 0), Vector2f(5, window->getSize().y), sf::Color::Blue, Vector2f(0, 0), ShapeType::Rectangle);
	LineRight->SetAnchors(Vector2f(1, 0));
    LineDown = new GameObject(Vector2f(0, window->getSize().y), Vector2f(window->getSize().x, 5), sf::Color::Blue, Vector2f(0, 0), ShapeType::Rectangle);
    LineDown->SetAnchors(Vector2f(0, 1));
    InputManager::Initialize();
}

App::~App()
{
    delete Bullet, Cannon, Brick, BIG_BALL;
    delete &LineUp, &LineLeft, &LineRight, &LineDown;
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

bool colliding = false;

void App::Update() {
    deltaTime = clock->restart();
    float dTs = deltaTime.asSeconds();

    Bullet->Update(dTs);
    Cannon->Update(dTs);
    Brick->Update(dTs);
    BIG_BALL->Update(dTs);
    LineUp->Update(dTs);
	LineLeft->Update(dTs);
    LineRight->Update(dTs);
	LineDown->Update(dTs);

    if (Bullet->CollidesWith(LineUp)) {
        Vector2f vel = Bullet->Velocity();
        Bullet->SetVelocity(Vector2f(vel.x, vel.y * -1));
    }
    if (Bullet->CollidesWith(LineDown)) {
        Vector2f vel = Bullet->Velocity();
        Bullet->SetVelocity(Vector2f(vel.x, vel.y * -1));
    }
    if (Bullet->CollidesWith(LineRight)) {
        Vector2f vel = Bullet->Velocity();
        Bullet->SetVelocity(Vector2f(vel.x * -1, vel.y));
    }
    if (Bullet->CollidesWith(LineLeft)) {
        Vector2f vel = Bullet->Velocity();
        Bullet->SetVelocity(Vector2f(vel.x*-1, vel.y));
    }

    if (InputManager::Instance->isMouseDown()) {
        cout << "Button pressed !";
    }

    Vector2i pos = InputManager::Instance->mousePosition(*window);

    Koko->SetPosition(Vector2f(pos.x, pos.y));

    Koko->SetColor(Koko->CollidesWith(Kiki) ? sf::Color::Green : sf::Color::Magenta);

    Vector2f dir = Vector2f(pos.x, pos.y) - Cannon->Position();
    Mathematics::Normalize(&dir);

    float angle = Mathematics::Clamp(Mathematics::AngleFromDirection(dir) * Mathematics::RAD2DEG, -45, 45);
    Cannon->SetRotationAngle(angle);

    if (Bullet->CollidesWith(Brick)) { //|| Bullet->CollidesWith(LineLeft)) {
        Bullet->SetVelocity(Bullet->Velocity() * -1.f);
    }
}

void App::Render() {
    window->clear(Color::White);

    LineUp->Render(window);
    LineLeft->Render(window);
    LineRight->Render(window);
    LineDown->Render(window);

    Bullet->Render(window);
    Cannon->Render(window);
    Brick->Render(window);

    Kiki->Render(window);
    Koko->Render(window);

    CircleShape s(35);
    s.setFillColor(sf::Color::Red);
    Cannon->SetAnchors(Vector2f(0.5, 0.5));
    s.setPosition(Cannon->Position() - Vector2f(Cannon->Size().x * Cannon->Anchors().x, Cannon->Size().y * Cannon->Anchors().y) * 0.5f);
    window->draw(s);

    BIG_BALL->Render(window);

    window->display();
}