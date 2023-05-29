#pragma once

#include <string>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

#include "Engine.h"

using namespace std;

class TextureRenderer
{
public:
	static TextureRenderer* GetInstance()
	{
		if (TextureRendererInstance != nullptr) return TextureRendererInstance;
		else return TextureRendererInstance = new TextureRenderer();
	}
	TextureRenderer() {};
	bool Load(string textureId, string filename, SDL_Renderer* renderer);
	void Draw(string textureId, SDL_Rect position, SDL_RendererFlip flip, SDL_Renderer* renderer);
	void DrawTile(string tilesetID, int tileWidth, int tileHeight, int x, int y, SDL_RendererFlip flip);

	void DrawAnimationTile(string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip);

private:
	map<string, SDL_Texture*> TextureMap;
	static TextureRenderer* TextureRendererInstance;
};

