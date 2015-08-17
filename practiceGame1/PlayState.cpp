// include SFML
#include <SFML/Graphics.hpp>

// include local classes
#include "ball.h"
#include "paddle.h"

// include header file
#include "PlayState.hpp"

PlayState::PlayState() {
    // stub
}

PlayState::PlayState(const sf::RenderWindow &window) {

    // Creating Ball
    float ballRadius = 10.0f;
    sf::Color ballColor(255, 255, 255, 255);
    sf::Vector2f ballStartPos((window.getSize().x / 2.0f) - ballRadius,
                              (window.getSize().y / 2.0f) - ballRadius);
    sf::Vector2f ballStartSpeed(300.0f, -150.0f);    
    ball = Ball(ballRadius, ballColor,
              ballStartPos, ballStartSpeed);
    
    // Creating Paddle
    sf::Vector2f paddleSize(10.0f, window.getSize().y / 7.0f);
    sf::Color paddleColor(255, 255, 255, 255);
    sf::Vector2f paddleStartPos(
        80.0f,
        window.getSize().y / 2.0f - paddleSize.y / 2.0f);
    float paddleStartSpeed = 650.0f;
    paddle1 = Paddle(paddleSize, paddleColor,
                     paddleStartPos, paddleStartSpeed);

    paddle2 = Paddle(paddleSize, paddleColor,
                     sf::Vector2f(window.getSize().x - paddleStartPos.x - paddleSize.x, paddleStartPos.y),
                     paddleStartSpeed - 400.0);

}

void PlayState::draw(sf::RenderWindow &window) {

    window.clear(sf::Color::Black);
    window.draw(ball.getDrawable());
    window.draw(paddle1.getDrawable());
    window.draw(paddle2.getDrawable());
    window.display();

}

void PlayState::update(const sf::RenderWindow &window,
                       const sf::Time &tslu) {

    ball.update(window, tslu);
    paddle1.update(window, tslu);
    paddle2.update(window, tslu);

    timmer += tslu.asMilliseconds();
    if (timmer >= PADDLE_MOVE_TIME) {

        timmer = 0.0f;
        sf::CircleShape circle = *dynamic_cast<const sf::CircleShape *>(&(ball.getDrawable()));
        sf::RectangleShape rectangle = *dynamic_cast<const sf::RectangleShape *>(&(paddle2.getDrawable()));
        if (circle.getPosition().y + circle.getRadius() < rectangle.getPosition().y + rectangle.getSize().y / 2.0f) {

            paddle2.setDirection(Paddle::UP);
            paddle2Dir = Paddle::UP;

        }
        else if (circle.getPosition().y + circle.getRadius() > rectangle.getPosition().y + rectangle.getSize().y / 2.0f) {

            paddle2.setDirection(Paddle::DOWN);
            paddle2Dir = Paddle::DOWN;

        }
        else {

            paddle2.setDirection(Paddle::STILL);
            paddle2Dir = Paddle::STILL;

        }

    }
    else
        paddle2.setDirection(paddle2Dir);

    sf::Vector2f *least = ball.collides(paddle1.getDrawable());
    if (least != NULL) {

        ball.move(sf::Vector2f(least->x, least->y));
        ball.bounce(sf::Vector2f(least->x, least->y));

        delete least;
        least = NULL;

    }

    least = ball.collides(paddle2.getDrawable());
    if (least != NULL) {

        ball.move(sf::Vector2f(least->x, least->y));
        ball.bounce(sf::Vector2f(least->x, least->y));

        delete least;
        least = NULL;

    }

}

void PlayState::handleInput() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        paddle1.setDirection(Paddle::UP);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        paddle1.setDirection(Paddle::DOWN);

}