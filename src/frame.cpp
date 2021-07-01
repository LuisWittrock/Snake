#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace sf;

class Frame
{
    public:
        RenderWindow window;
        Event event;
        int WINDOW_HEIGHT = 800;
        int WINDOW_WIDTH = 800;
        Frame()
        {
            window.setFramerateLimit(10);
        }
};
