#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
	
  SDL_Surface *surface = SDL_GetWindowSurface(sdl_window);
  if (TTF_Init() < 0) {
    // Error handling code
    std::cerr << "TTF_INIT RETURNS: " << TTF_Init() << "\n";
  }
  font = TTF_OpenFont("../src/DejaVuSans.ttf", 25);
  sdl_MsgTexture = nullptr;
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, std::vector<MapTile> const &_tileList) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  //SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  for(auto foodTiles : _tileList)
  {
    //std::cout << "rendering a food piece" << std::endl;
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = foodTiles.X() * block.w;
    block.y = foodTiles.Y() * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);  
  }

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);

    if(global_waitingOnPlayers == true)
    {
      if (nullptr == sdl_MsgTexture) SDL_GenerateMessageTexture(sdl_renderer, "Waiting for player", 90, 50, 50, 200);

    //  std::cout << "We are waiting\n";
    }
    else
    {
      sdl_MsgTexture = nullptr;
    //  std::cout << "We cleared it\n";
    }
      
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);

    //  std::cout << "We are dead\n";
    // snake is dead, print a game over message (only good for single player)
    if(nullptr == sdl_MsgTexture) SDL_GenerateMessageTexture(sdl_renderer, "You Are Dead", 90, 250, 0, 0);

  }

  if(sdl_MsgTexture != nullptr)
  {

    SDL_Rect rect;
    rect.w = 500; // gives good aspect ratio
    rect.h = 200;
    rect.x = (kScreenWidth / 2) - (rect.w / 2); // centre the screen
    rect.y = (kScreenHeight / 2) - (rect.h / 2);
    SDL_RenderCopy(sdl_renderer, sdl_MsgTexture, nullptr, &rect);
  }

  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::SDL_GenerateMessageTexture(SDL_Renderer *sdl_renderer, std::string msg, int alpha, int red, int green, int blue)
{
  SDL_Color color = SDL_Color();

  if (font == NULL)
  {
    std::cout << "Err: No Font";
    return;
  }

  color.a = alpha;
  color.r = red;
  color.g = green;
  color.b = blue;
  
  SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, msg.c_str(), color);

  sdl_MsgTexture = SDL_CreateTextureFromSurface(sdl_renderer, surfaceMessage);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
