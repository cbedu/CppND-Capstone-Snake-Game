#ifndef PLAYER_H
#define PLAYER_H

#include "snake.h"
#include "controller.h"
#include <memory>

class Player
{
    public:
    Player(std::unique_ptr<Controller> controller_, std::unique_ptr<Snake> snake_)
        :_controller(controller_), _snake(snake_) {};
    ~Player();  // nothing to release

    updateDirection();  //controller handle input
    updateSnake();  //snake updateHead updateBody

    private:
    std::unique_ptr<Controller> _controller;
    std::unique_ptr<Snake> _snake;
}

#endif