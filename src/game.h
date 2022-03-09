#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "MapTile.hpp"
#include <memory>
#include <vector>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, std::vector<MapTile> &&_tileList);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration, int numPlayers);
  void Run(Controller const &controller, Renderer &renderer,
            std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  std::vector<MapTile> tileList_;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  size_t gridW;
  size_t gridH;

  void PlaceFood();
  void PlaceBarriers();
  void PlaceTiles();
  void Update();
};

#endif