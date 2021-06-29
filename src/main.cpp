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

int main()
{
    Frame frame;
    Panel panel;
    panel.drawWindow();
}