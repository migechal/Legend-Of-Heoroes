#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL_keyboard.h>
class Keyboard
{
	Keyboard(){};
	std::map<SDL_Scancode, bool> keyboard;
	void getInput();
	const Uint8 *state;

public:
	static Keyboard &getInstance();
	bool isPressed(std::vector<SDL_Scancode> buttons);
};
