#include <iostream>
#include <SFML/Graphics.hpp>
#include "App.hpp"

int main(int argc, char* argv[]) {
    App* app = new App(1280, 720);
    app->Loop();
    
    return 0;
}