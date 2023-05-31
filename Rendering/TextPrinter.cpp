#include "TextPrinter.h"

TextPrinter::TextPrinter(SDL_Renderer* aRenderer)
{
	if (TTF_Init() < 0)
	{
		SDL_Log("Error initializing ttf: %s", SDL_GetError());
	}
	ImageRenderer = aRenderer;
	Font = TTF_OpenFont("Resources/Fonts/lucotecia.black.ttf", 40);
	FontColor = { 200, 85, 78, 255};
	
}

TextPrinter::~TextPrinter()
{
	SDL_DestroyTexture(Text);
	Text = nullptr;
	SDL_DestroyRenderer(ImageRenderer);
	ImageRenderer = nullptr;
}

void TextPrinter::PrintText(string text, int x, int y)
{
	TextRect.x = x;
	TextRect.y = y;

	SDL_Surface* aTextSurface = TTF_RenderText_Solid(Font, text.c_str(), FontColor);
	if (ImageRenderer != nullptr && aTextSurface != nullptr)
		Text = SDL_CreateTextureFromSurface(ImageRenderer, aTextSurface);
	SDL_FreeSurface(aTextSurface);
	aTextSurface = nullptr;
	SDL_QueryTexture(Text, nullptr, nullptr, &TextRect.w, &TextRect.h);
	SDL_RenderCopy(ImageRenderer, Text, nullptr, &TextRect);
	SDL_DestroyTexture(Text);
}
