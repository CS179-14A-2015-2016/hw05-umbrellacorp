#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int window_width = 1200;
int window_height = 800;
int ball_radius = 50;
int paddle_radius = 100;
//int paddle_width = 50;
//int paddle_height = 200;

int score_left_value = 0;
int score_right_value = 0;

string to_string(int x)
{
    ostringstream os;
    os << x;
    return os.str();
}

bool paddle_left_down = 0;
bool paddle_left_up = 0;
bool paddle_right_down = 0;
bool paddle_right_up = 0;
int paddle_speed = 10;
int paddle_left_y = window_height / 2;
int paddle_right_y = window_height / 2;
int ball_1_x = window_width / 2;
int ball_1_y = window_height / 2 - 50;
int ball_2_x = window_width / 2;
int ball_2_y = window_height / 2 + 50;
int ball_1_x_speed = 5;
int ball_1_y_speed = 5;
int ball_2_x_speed = -5;
int ball_2_y_speed = -5;

double fps = 60;
sf::Time mspf = sf::milliseconds(1000/fps);

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(window_width, window_height), "Pong 2.0", sf::Style::Close);
    
    sf::CircleShape ball_1(ball_radius);
    ball_1.setOrigin(ball_radius,ball_radius);
    ball_1.setFillColor(sf::Color(100, 250, 50));
    ball_1.setPosition(ball_1_x, ball_1_y);
    
    sf::CircleShape ball_2(ball_radius);
    ball_2.setOrigin(ball_radius,ball_radius);
    ball_2.setFillColor(sf::Color(100, 250, 50));
    ball_2.setPosition(ball_2_x, ball_2_y);
    
    sf::CircleShape paddle_left(paddle_radius);
    paddle_left.setOrigin(paddle_radius,paddle_radius);
    paddle_left.setFillColor(sf::Color(100, 150, 50));
    paddle_left.setPosition(0, paddle_left_y);
    
    sf::CircleShape paddle_right(paddle_radius);
    paddle_right.setOrigin(paddle_radius,paddle_radius);
    paddle_right.setFillColor(sf::Color(100, 150, 50));
    paddle_right.setPosition(window_width, paddle_right_y);
    
    sf::Text score_left_display;
    sf::Text score_right_display;
    
    sf::Font font;
    if(!font.loadFromFile("AlegreyaSans-Regular.ttf"))
    {
        return 0;
    }
    
    score_left_display.setFont(font);
    score_left_display.setCharacterSize(100);
    score_left_display.setColor(sf::Color::Green);
    score_left_display.setOrigin(25, 50);
    score_left_display.setPosition( 50, 50);
    
    score_right_display.setFont(font);
    score_right_display.setCharacterSize(100);
    score_right_display.setColor(sf::Color::Green);
    score_right_display.setOrigin(25, 50);
    score_right_display.setPosition(window_width - 50, 50);
    
    /**
     sf::RectangleShape paddle_left(sf::Vector2f(paddle_width, paddle_height));
     paddle_left.setOrigin(paddle_width / 2, paddle_height / 2);
     paddle_left.setFillColor(sf::Color(100, 150, 50));
     paddle_left.setPosition(35, window_height / 2);
     
     sf::RectangleShape paddle_right(sf::Vector2f(paddle_width, paddle_height));
     paddle_right.setOrigin(paddle_width / 2, paddle_height / 2);
     paddle_right.setFillColor(sf::Color(100, 150, 50));
     paddle_right.setPosition(window_width - 35, window_height / 2);
     **/
    
    while (window.isOpen())
    {
        //start the clock
        sf::Clock frame_timer;
        
        //Read Inputs
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            if (paddle_left_y > 100)
            {
                paddle_left_y += -paddle_speed;
            }
            else
            {
                paddle_left_y = 100;
            }
            paddle_left.setPosition(0, paddle_left_y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (paddle_left_y < window_height - 100)
            {
                paddle_left_y += paddle_speed;
            }
            else
            {
                paddle_left_y = window_height - 100;
            }
            
            paddle_left.setPosition(0, paddle_left_y);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        {
            
            if (paddle_right_y > 100)
            {
                paddle_right_y += -paddle_speed;
            }
            else
            {
                paddle_right_y = 100;
            }
            paddle_right.setPosition(window_width, paddle_right_y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        {
            if (paddle_right_y < window_height - 100)
            {
                paddle_right_y += paddle_speed;
            }
            else
            {
                paddle_right_y = window_height - 100;
            }
            paddle_right.setPosition(window_width, paddle_right_y);
        }
        
        //Simulation
        
        //Ball 1 and Ball 2 collision
        if (((ball_1_x - ball_2_x) >= (2*ball_radius)) || ((ball_1_y - ball_2_y) >= (2*ball_radius)))
        {
            do
            {
                ball_1_x_speed = ball_2_x_speed;
                ball_2_x_speed = ball_1_x_speed;
            }while (((ball_1_x - ball_2_x) >= (2*ball_radius)));
            
            do
            {
                ball_1_y_speed = ball_2_y_speed;
                ball_2_y_speed = ball_2_x_speed;
            }while (((ball_1_y - ball_2_y) >= (2*ball_radius)));
        }
        
        //Ball 1 collision Paddle Left or Right
        else if (((ball_1_x <= (0 + paddle_radius)) && (ball_1_y <= (paddle_left_y-ball_radius))) || ((ball_1_x >= (window_width - paddle_radius)) && (ball_1_y <= (paddle_right_y-ball_radius))))
        {
            if ((ball_1_x <= (0 + paddle_radius)) && (ball_1_y <= (paddle_left_y-ball_radius)))
            {
                ball_1_x_speed = -(ball_1_x_speed + paddle_speed);
            }
            else if (((ball_1_x >= (window_width - paddle_radius))) && (ball_1_y <= (paddle_right_y-ball_radius)))
            {
                ball_1_y_speed = -(ball_1_y_speed + paddle_speed);
            }
        }
        
        //Ball 1 collision Left or Right
        else if (((ball_1_x - ball_radius) <= 0) || ((ball_1_x + ball_radius) >= window_width))
        {
            if ((ball_1_x - ball_radius) <= 0)
            {
                ball_1_x_speed = -ball_1_x_speed;
                ++score_right_value;
            }
            
            else if ((ball_1_x + ball_radius) >= window_width)
            {
                ball_1_x_speed = -ball_1_y_speed;
                ++score_left_value;
            }
        }
        
        //Ball 1 collision Up or Down
        else if (((ball_1_y - ball_radius) >= window_height) || ((ball_1_y - ball_radius) <= 0))
        {
            ball_1_y_speed = -ball_1_y_speed;
        }
        
        //Ball 2 collision Paddle Left or Right
        else if (((ball_2_x <= (0 + paddle_radius)) && (ball_2_y <= (paddle_left_y-ball_radius))) || ((ball_2_x >= (window_width - paddle_radius)) && (ball_2_y <= (paddle_right_y-ball_radius))))
        {
            ball_2_x_speed = -(ball_2_x_speed + paddle_speed);
            ball_2_y_speed = -(ball_2_y_speed + paddle_speed);
        }
        
        //Ball 2 collision Left or Right
        else if (((ball_2_x - ball_radius) <= 0) || ((ball_2_x + ball_radius) >= window_width))
        {
            if ((ball_2_x - ball_radius) <= 0)
            {
                ball_2_x_speed = -ball_2_x_speed;
                ++score_right_value;
            }
            
            else if ((ball_2_x + ball_radius) >= window_width)
            {
                ball_2_x_speed = -ball_2_y_speed;
                ++score_left_value;
            }
        }
        
        //Ball 2 collision Up or Down
        else if (((ball_2_y - ball_radius) >= window_height) || ((ball_2_y - ball_radius) <= 0))
        {
            ball_2_y_speed = -ball_2_y_speed;
        }
        
        //update position
        else
        {
            ball_1_x += ball_1_x_speed;
            ball_1_y += ball_1_y_speed;
            ball_2_x += ball_2_x_speed;
            ball_2_y += ball_2_y_speed;
        }
        
        //Draw
        window.clear(sf::Color::Black);
        
        //balls
        window.draw(ball_1);
        window.draw(ball_2);
        
        //paddles
        window.draw(paddle_left);
        window.draw(paddle_right);
        
        //scores
        string converted_score_left = to_string(score_left_value);
        //score_left_display.setFont(font);
        score_left_display.setString(converted_score_left);
        //score_left_display.setCharacterSize(100);
        //score_left_display.setPosition( 20, 10);
        //score_left_display.setColor(sf::Color::Green);
        window.draw(score_left_display);
        
        string converted_score_right = to_string(score_right_value);
        //score_right_display.setFont(font);
        score_right_display.setString(converted_score_right);
        //score_right_display.setCharacterSize(100);
        //score_right_display.setPosition(window_width - 20, 10);
        //score_right_display.setColor(sf::Color::Green);
        window.draw(score_right_display);
        
        //Final Display
        window.display();
        
        //Synchronize Time Step
        sf::Time loop_duration = frame_timer.getElapsedTime();
        
        if (loop_duration < mspf)
        {
            sf::sleep(mspf - loop_duration);
        }
        frame_timer.restart();
    }
    
    return 0;
}