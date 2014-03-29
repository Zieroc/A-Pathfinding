#ifndef BUTTON_H
#define BUTTON_H

#include "CC_Texture.h"
#include "InputHandler.h"
#include "Vector2.h"

class Button
{
public:
	Button(CC_Texture* texture, Vector2 position, void (*callback)(void* ptrObj), void* ptrObj);
	~Button();
	void Draw(SDL_Renderer* renderer);
	void HandleInput(InputHandler* input);
private:
	CC_Texture* m_p_Texture;
	Vector2 m_Position;
	SDL_Rect m_Bounds;
	void (*m_p_CallBack)(void* ptrObj);
	bool m_Clicked;
	void* m_p_PtrObj; //For the callback function
};

#endif