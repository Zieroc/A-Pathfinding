#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "Debug.h"
#include <SDL.h>

class InputHandler
{
public:
	enum MouseButton {LeftButton = 1, MiddleButton, RightButton};
	InputHandler();
	~InputHandler();
	void Update();
	bool KeyPressed(SDL_Keycode key);
	bool MousePressed(MouseButton button);
	int GetMouseX();
	int GetMouseY();
private:
	const Uint8* m_p_KeyboardState; //The current state of the keyboards
	int m_MouseX;
	int m_MouseY;
};

#endif