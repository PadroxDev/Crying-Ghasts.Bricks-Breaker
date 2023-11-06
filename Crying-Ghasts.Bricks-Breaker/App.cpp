#include <SFML/Graphics.hpp>
#include "App.hpp"
#include "GameObject.hpp"

const unsigned int FRAME_CAP = 200;

RectangleShape* shape;
RectangleShape* shaaaaa;
GameObject* obj;
GameObject* rayan;

App::App(int width, int height) {
	InitWindow(width, height);
	clock = new Clock();

    shape = new RectangleShape(Vector2f(1, 0.5f) * 200.0f);
    Vector2f pos(30, 30);
    Vector2f size(1, 1);
    Vector2f dir(30, 0);
    obj = new GameObject(pos, size, shape, Color(0, 180, 0, 255), dir);

    shaaaaa = new RectangleShape(Vector2f(0.5, 1) * 50.0f);
    Vector2f edino(1000, 20);
    Vector2f agale(1, 1);
    Vector2f garama(-20, 0);
    rayan = new GameObject(edino, agale, shaaaaa, Color(255, 255, 0, 255), garama);
}

App::~App()
{
    delete shape;
    delete obj;
}

void App::InitWindow(int width, int height) {
    window = new RenderWindow(VideoMode(width, height), "Crying Ghasts", Style::Default);
    window->setFramerateLimit(FRAME_CAP);
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
    deltaTime = clock->getElapsedTime();
    
    obj->Update(deltaTime.asSeconds());
    rayan->Update(deltaTime.asSeconds());

    if (obj->CollidesWith(rayan)) {
        cout << deltaTime.asSeconds() << endl;
        //rayan->Direction *= -1.0f;
        //obj->Direction *= -1.0f;
    }

    clock->restart();
}

void App::Render() {
    window->clear(Color::White);

    obj->Render(window);
    rayan->Render(window);

    window->display();
}