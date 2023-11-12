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

    Brick = new GameObject(Vector2f(1280*0.5f, 190), Vector2f(150, 60), ShapeType::Rectangle, sf::Color(139, 69, 19));
    Bullet = new GameObject(Vector2f(430, 300), Vector2f(75, 75), ShapeType::Rectangle, sf::Color::Red);
    Cannon = new GameObject(Vector2f(1280 * 0.5f, 600), Vector2f(150, 150), ShapeType::Triangle, sf::Color::Blue);
 //   LineUp = new GameObject(Vector2f(0, 0), Vector2f(window->getSize().x, 5), sf::Color::Blue, Vector2f(0, 0), ShapeType::Rectangle);
 //   LineUp->SetAnchors(Vector2f(0, 0));
 //   LineLeft = new GameObject(Vector2f(0, 0), Vector2f(5, window->getSize().y), sf::Color::Blue, Vector2f(0, 0), ShapeType::Rectangle);
 //   LineLeft->SetAnchors(Vector2f(0, 0));
	//LineRight = new GameObject(Vector2f(window->getSize().x, 0), Vector2f(5, window->getSize().y), sf::Color::Blue, Vector2f(0, 0), ShapeType::Rectangle);
	//LineRight->SetAnchors(Vector2f(1, 0));
 //   LineDown = new GameObject(Vector2f(0, window->getSize().y), Vector2f(window->getSize().x, 5), sf::Color::Blue, Vector2f(0, 0), ShapeType::Rectangle);
 //   LineDown->SetAnchors(Vector2f(0, 1));
    InputManager::Initialize();
}

App::~App()
{
    delete Bullet, Cannon, Brick, BIG_BALL;
    //delete &LineUp, &LineLeft, &LineRight, &LineDown;
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

    Bullet->Update(dT);
    Cannon->Update(dT);
    Brick->Update(dT);
 //   BIG_BALL->Update(dTs);
 //   LineUp->Update(dTs);
	//LineLeft->Update(dTs);
 //   LineRight->Update(dTs);
	//LineDown->Update(dTs);

    //if (Bullet->CollidesWith(LineUp)) {
    //    Vector2f vel = Bullet->Velocity();
    //    Bullet->SetVelocity(Vector2f(vel.x, vel.y * -1));
    //}
    //if (Bullet->CollidesWith(LineDown)) {
    //    Vector2f vel = Bullet->Velocity();
    //    Bullet->SetVelocity(Vector2f(vel.x, vel.y * -1));
    //}
    //if (Bullet->CollidesWith(LineRight)) {
    //    Vector2f vel = Bullet->Velocity();
    //    Bullet->SetVelocity(Vector2f(vel.x * -1, vel.y));
    //}
    //if (Bullet->CollidesWith(LineLeft)) {
    //    Vector2f vel = Bullet->Velocity();
    //    Bullet->SetVelocity(Vector2f(vel.x*-1, vel.y));
    //}

    //if (InputManager::Instance->isMouseDown()) {
    //    cout << "Button pressed !";
    //}

    //Vector2i pos = InputManager::Instance->mousePosition(*window);

    //Koko->SetPosition(Vector2f(pos.x, pos.y));

    //Koko->SetColor(Koko->CollidesWith(Kiki) ? sf::Color::Green : sf::Color::Magenta);

    //Vector2f dir = Vector2f(pos.x, pos.y) - Cannon->Position();
    //Mathematics::Normalize(&dir);

    //float angle = Mathematics::Clamp(Mathematics::AngleFromDirection(dir) * Mathematics::RAD2DEG, -45, 45);
    //Cannon->SetRotationAngle(angle);

    if (Bullet->CollidesWith(Brick)) { 
        Bullet->setVelocity(Bullet->Velocity() * -1.f);
    }
}

void App::Render() {
    window->clear(Color::White);

    //LineUp->Render(window);
    //LineLeft->Render(window);
    //LineRight->Render(window);
    //LineDown->Render(window);

    Bullet->Render(window);
    Cannon->Render(window);
    Brick->Render(window);

    window->display();
}