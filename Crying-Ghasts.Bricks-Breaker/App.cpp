#include "App.hpp"

const unsigned int FRAME_CAP = 200;

App::App(int width, int height) {
	InitWindow(width, height);
	clock = new Clock();
}

App::~App()
{}

void App::InitWindow(int width, int height) {
    cout << "camembert";
    window->create(VideoMode(width, height), "Crying Ghasts", Style::Default);
    cout << "wut";
    window->setFramerateLimit(FRAME_CAP);
}

void App::Loop() {
    cout << "uwu";
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
    clock->restart();

    system("cls");
    cout << clock->getElapsedTime().asSeconds() << endl;
}

void App::Render() {

}