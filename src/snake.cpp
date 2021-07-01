#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "frame.cpp"

using namespace std;
using namespace sf;


class Snake : Frame
{
    public:
        RectangleShape rect;
        RectangleShape apple;
        pair<int, int> velocity; //xVel, yVel;
        pair<int, int> applePos; //xPos, yPos
        vector<pair<int, int>> pos; //xPos, yPos;
        int snakelength = 0;

        Snake()
        {
            //apple related
            apple.setFillColor(sf::Color(255,25,25));
            apple.setSize(Vector2f(25.f, 25.f));
            
            //snake related
            rect.setSize(Vector2f(25.f, 25.f));
            rect.setFillColor(sf::Color(25,255,25));
            cout << "snake object constructor \n";
            velocity.first = 25;
            velocity.second = 0;
            pos.push_back(make_pair(WINDOW_HEIGHT/2,WINDOW_WIDTH/2));
        }

        void move() //set the current snake element position to the previous snake element
        {
            for(int i = snakelength; i>0; i--)
            {
                pos[i].first = pos[i-1].first;
                pos[i].second = pos[i-1].second;
            }
            pos[0].first += velocity.first;
            pos[0].second += velocity.second;
        }

        RectangleShape getRectangleShape()
        {
            return rect;
        }
        RectangleShape getApple()
        {
            return apple;
        }
        
        void SnakeReset()
        {
            //reset the snake here.
            velocity.first = 25;
            velocity.second = 0;
            snakelength = 0;
            pos.clear();
            pos.push_back(make_pair(WINDOW_HEIGHT/2,WINDOW_WIDTH/2));

        }

        void eatApple()
        {
            snakelength++;
            spawnApple();

            //get longer
            pos.push_back(pos[0]);
        }

        void spawnApple()
        {
            int maxX = WINDOW_WIDTH;
            int maxY = WINDOW_HEIGHT;
            srand(time(NULL));
            applePos.first = (rand() % maxX) % 25 * 25;

            applePos.second = (rand() % maxY) % 25 * 25;

            apple.setPosition(applePos.first, applePos.second);
        }

        pair<int, int> getSnakePos()
        {
            return pos[0];
        }
        pair<int, int> getApplePos()
        {
            return applePos;
        }
};  