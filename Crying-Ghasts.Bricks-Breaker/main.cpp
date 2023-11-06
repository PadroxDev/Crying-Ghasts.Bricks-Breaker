#include <iostream>
#include <SFML/Graphics.hpp>
#include "App.hpp"

const unsigned int FRAME_CAP = 200;

int main(int argc, char* argv[]) {
    App* app = new App(1280, 720);
    app->Loop();
    
    return 0;
}