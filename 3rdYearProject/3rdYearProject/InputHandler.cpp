#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler()
{
	m_p_KeyboardState = SDL_GetKeyboardState(NULL);
	SDL_GetMouseState(&m_MouseX, &m_MouseY);
}

InputHandler::~InputHandler()
{
}

void InputHandler::Update()
{
	SDL_PumpEvents();
	SDL_GetMouseState(&m_MouseX, &m_MouseY);
}

bool InputHandler::KeyPressed(SDL_Keycode key)
{
	return m_p_KeyboardState[SDL_GetScancodeFromKey(key)];
}

bool InputHandler::MousePressed(MouseButton button)
{
	SDL_PumpEvents();
	return(SDL_GetMouseState(&m_MouseX, &m_MouseY) & SDL_BUTTON(button));
}

int InputHandler::GetMouseX()
{
	return m_MouseX;
}

int InputHandler::GetMouseY()
{
	return m_MouseY;
}