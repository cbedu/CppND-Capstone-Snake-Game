#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "snake.h"
#include "global_share.h"
#include "MapTile.hpp"
#include <string>

extern std::size_t kScreenWidth;
extern std::size_t kScreenHeight;

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, std::vector<MapTile> const &_tileList);
  void UpdateWindowTitle(int score, int fps);
  void SDL_GenerateMessageTexture(SDL_Renderer *sdl_renderer, std::string msg, int alpha, int red, int green, int blue);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *sdl_MsgTexture;
  TTF_Font *font;
  
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
