#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "snake.h"
#include <string>

constexpr std::size_t kScreenWidth{640};
constexpr std::size_t kScreenHeight{640};

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
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
