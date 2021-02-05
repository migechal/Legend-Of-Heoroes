#include <map>
#include <string>
#include <SDL2/SDL_keyboard.h>
class Input{
	static Input *instance;
	Input();
	std::map<std::string, bool> keyboard;
	void getInput();
	const Uint8 *state;
public:
	static Input *getInstance();
	bool isPressed(std::string button);
};
