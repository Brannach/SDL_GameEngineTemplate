#include "TextureRenderer.h"

TextureRenderer* TextureRenderer::TextureRendererInstance = nullptr;
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

void TextureRenderer::DrawAnimationTile(string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect dest = { (int)x, (int)y, tileSize, tileSize };
	SDL_Rect source = { frame * tileSize, row * tileSize, tileSize, tileSize };
	SDL_RenderCopyEx(Engine::GetInstance().GetRenderer(), TextureMap[tilesetID], &source, &dest, 0, nullptr, flip);
	SDL_SetRenderDrawColor(Engine::GetInstance().GetRenderer(), 126, 126, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(Engine::GetInstance().GetRenderer(), &dest);

}

void TextureRenderer::DrawTile(string tilesetID, int tileWidth, int tileHeight, int x, int y, SDL_RendererFlip flip)
{
	SDL_Rect dest = { (int)x, (int)y, tileWidth, tileHeight };
	SDL_Rect source = { 0, 0, tileWidth, tileHeight };
	SDL_RenderCopyEx(Engine::GetInstance().GetRenderer(), TextureMap[tilesetID], &source, &dest, 0, nullptr, flip);
	SDL_SetRenderDrawColor(Engine::GetInstance().GetRenderer(), 126, 126, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(Engine::GetInstance().GetRenderer(), &dest);
}
