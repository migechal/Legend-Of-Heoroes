#include <map>
#include <string>
#include <SDL2/SDL_keyboard.h>
class Keyboard
{
	Keyboard(){};
	std::map<SDL_Scancode, bool> keyboard;
	void getInput();
	const Uint8 *state;

public:
	static Keyboard &getInstance();
	bool isPressed(SDL_Scancode button);
};
