#include "TextureRenderer.h"

bool TextureRenderer::Load(string textureId, string filename, SDL_Renderer* renderer)
{
	if (renderer == nullptr)
	{
		SDL_Log("Invalid renderer");
		return false;
	}
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr)
	{
		SDL_Log("Couldn't load image from file: %s", SDL_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
	{
		SDL_Log("Couldn't create texture: %s", SDL_GetError());
		return false;
	}
	SDL_FreeSurface(surface);
	TextureMap[textureId] = texture;
	return true;
}

void TextureRenderer::Draw(string textureId, SDL_Rect position, SDL_RendererFlip flip, SDL_Renderer* renderer)
{
	int textureWidth, textureHeight;

	SDL_QueryTexture(TextureMap[textureId], nullptr, nullptr, &textureWidth, &textureHeight);
	SDL_Rect source = { 0, 0, textureWidth, textureHeight };
	SDL_RenderCopyEx(renderer, TextureMap[textureId], &source, &position, 0, nullptr, flip);
}
