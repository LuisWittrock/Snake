#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "frame.cpp"
#include "snake.cpp"

using namespace std;
using namespace sf;

class Panel : Frame
{
    public:
        Snake snake;
        bool gameover = false;
        Clock clock;
        Panel panel()
        {
            snake.spawnApple();
        }

        void checkCollision()
        {
            if(snake.getSnakePos() == snake.getApplePos())
            {
                snake.eatApple();
            }
            for(int i = 1; i<snake.snakelength; i++)
            {
                if(snake.getSnakePos() == snake.pos[i]) gameover = true;
            }
            if(snake.getSnakePos().first < 0 || snake.getSnakePos().first >= WINDOW_WIDTH || snake.getSnakePos().second < 0 || snake.getSnakePos().second >= WINDOW_HEIGHT) gameover = true;
        }

        void move()
        {
            snake.move();
        }

        void redraw()
        {
            for(auto it:snake.pos) //drawing all the body parts of the snake
            {
                snake.rect.setPosition(Vector2f(it.first, it.second));
                window.draw(snake.getRectangleShape());
            }
            window.draw(snake.getApple());
        }

        void drawWindow()
        {
            window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");
            clock.restart();
            while(window.isOpen())
            {
                while(!gameover)
                {               

                    //get player input
                    if(Keyboard::isKeyPressed(Keyboard::Up)) 
                    {
                        snake.velocity.first = 0;
                        snake.velocity.second = -25;
                    }
                    if(Keyboard::isKeyPressed(Keyboard::Down)) 
                    {
                        snake.velocity.first = 0;
                        snake.velocity.second = 25;
                    }
                    if(Keyboard::isKeyPressed(Keyboard::Right)) 
                    {
                        snake.velocity.first = 25;
                        snake.velocity.second = 0;
                    }
                    if(Keyboard::isKeyPressed(Keyboard::Left)) 
                    {
                        snake.velocity.first = -25;
                        snake.velocity.second = 0;
                    }
                    Time elapsed = clock.getElapsedTime();
                    if(elapsed.asSeconds() >= 0.1)
                    {
                        move(); //move the snake
                        checkCollision(); //check for collisions

                        window.clear();
                        //rendering here
                        redraw();

                        window.display();
                        clock.restart();
                    }
                    

                    while(window.pollEvent(Frame::Frame::event)) //close window
                    {
                        if(event.type == Event::Closed) window.close();
                    }
                }
                //game gets reset
                snake.SnakeReset();
                gameover = false;               
            }
        }
};