#pragma once

#include <string>

struct SDL_Texture;
struct SDL_Renderer;

SDL_Texture* loadTexture(std::string path, SDL_Renderer* gRenderer);