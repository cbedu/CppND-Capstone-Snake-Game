#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <vector>
#include <memory>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  Game(std::size_t grid_width, std::size_t grid_height, std::vector<std::string>& playerNames);

  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration, int numPlayers);
  
  void Run(Controller const &controller, Renderer &renderer,
            std::size_t target_frame_duration);
  
  int GetScore() const;
  int GetSize() const;

 private:
  std::vector<std::unique_ptr<Snake>> snakes; // <<TODO>> # make vector of unique_ptr
  Snake snake;
  SDL_Point food; // <<TODO>> # also make vector? add timeout val

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif