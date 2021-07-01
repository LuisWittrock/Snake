#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "frame.cpp"
#include "panel.cpp"

using namespace std;
using namespace sf;

int main()
{
    Frame frame;
    Panel panel;
    panel.drawWindow();
}