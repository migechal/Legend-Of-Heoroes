#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "header/Init.h"
#include <string>
class Gui{
	SDL_Renderer* renderer;
	SDL_Window* window;
        SDL_DisplayMode windowDimensions;
        Init* init;
public:
    
    Gui(SDL_Window* window, SDL_Renderer* renderer, Init* init);

    void addText(std::string Text, SDL_Rect position, TTF_Font* font, SDL_Color color, size_t scale);
};