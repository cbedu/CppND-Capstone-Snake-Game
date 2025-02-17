#include "game.h"
#include <iostream>
#include "SDL.h"
#include "global_share.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, std::vector<MapTile> &&_tileList)
    : gridH(grid_height),
      gridW(grid_width),
      snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      tileList_{std::move(_tileList)} {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration, int numPlayers) {
                 this->Run(controller, renderer, target_frame_duration);
               }

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  /*if(tileList_.size() == 0){
      tileList_.emplace_back(MapTile(1,1,1));
  }*/

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, tileList_);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // <<TODO>> 1 Add screen rendered score...
    //renderer.UpdateScoreBoard(score);


    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() { // <<TODO>> ensure not to place on barrier
  int x, y;
  while (true) {
    x = random_w(engine) % gridW;
    y = random_h(engine) % gridH;

    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
        MapTile temp = MapTile(1, x, y);
        tileList_.emplace_back(temp);
//      food.x = x;
//      food.y = y;
      std::cout << "Food is at [" << x << "," << y << "]" << std::endl;
      return;
    }
  }
}

void Game::Update() {
  // <<TODO>> This will need to become a scan for whether any snake is kInitial
  //  This way we wait on "All Players Ready"
  if(snake.direction == Snake::Direction::kInitial)
  {
    //std::cout << "We are waiting\n";
    global_waitingOnPlayers = true;
    //return;
  }else{
    //std::cout << "Running\n";
    global_waitingOnPlayers = false;
    
  }

  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  for( auto tileIT = tileList_.begin() ; tileIT != tileList_.end(); ++tileIT)
    if (tileIT->X() == new_x && tileIT->Y() == new_y) {
        if(tileIT->IsPerm() == false)
        {
            tileList_.erase(tileIT);
            PlaceFood();
        }

        score++;
        // Grow snake and increase speed.
        snake.GrowBody();
        snake.speed += 0.02;

    break;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
