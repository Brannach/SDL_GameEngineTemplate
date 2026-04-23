#pragma once

#include <string>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

#include "..\Core\Engine.h"

using namespace std;

class TextureRenderer
{
public:
	static TextureRenderer& GetInstance()
	{
		static TextureRenderer TextureRendererInstance;
		return TextureRendererInstance;
	}
	TextureRenderer() {};
	~TextureRenderer()
	{
		for (auto& [key, texture] : TextureMap)
			SDL_DestroyTexture(texture);
	}
	bool Load(string textureId, string filename, SDL_Renderer* renderer);
	void Draw(string textureId, SDL_Rect position, SDL_RendererFlip flip, SDL_Renderer* renderer);
	void DrawTile(string tilesetID, int tileWidth, int tileHeight, int x, int y, SDL_RendererFlip flip, SDL_Renderer* renderer);

	void DrawAnimationTile(string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip, SDL_Renderer* renderer);

private:
	map<string, SDL_Texture*> TextureMap;
};

