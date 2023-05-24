#pragma once

#include <string>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class TextureRenderer
{
public:
	TextureRenderer() {};
	bool Load(string textureId, string filename, SDL_Renderer* renderer);
	void Draw(string textureId, SDL_Rect position, SDL_RendererFlip flip, SDL_Renderer* renderer);

private:
	map<string, SDL_Texture*> TextureMap;

};

