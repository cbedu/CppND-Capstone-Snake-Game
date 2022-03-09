#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"


// <<TODO>> # add hunger timeout
class Snake {
 public:
 // <<DONE>> 1 Add kInitial direction for initilisation
  enum class Direction { kUp, kDown, kLeft, kRight, kDead, kNone, kInitial };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kInitial;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif