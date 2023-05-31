#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

// This class uses SDL_ttf library to print text on the screen.
class TextPrinter
{
public:
	// Initializes the objects necessary to print the text
	TextPrinter(SDL_Renderer* aRenderer);

	// Frees the used objects
	~TextPrinter();

	// Prints a text one the given coordinates
	// Parameters:
	// - text: text to be displayed
	// - x, y: coordinates where text will be displayed
	void PrintText(string text, int x, int y);
private:
	TTF_Font* Font;
	SDL_Color FontColor;
	SDL_Surface* TextSurface;
	SDL_Texture* Text;
	SDL_Renderer* ImageRenderer;
	SDL_Rect TextRect = {0, 0, 0, 0};
};

