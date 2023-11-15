#include <iostream>
#include <SFML/Graphics.hpp>
#include "App.hpp"

int main(int argc, char* argv[]) {
    App::Initialize();
    App::GetInstance()->Loop();
    
    return 0;
}