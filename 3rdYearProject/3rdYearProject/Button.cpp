#include "Button.h"

Button::Button(CC_Texture* texture, Vector2 position, void (*callback)(void* ptrObj), void* ptrObj)
{
	m_p_Texture = texture;
	m_Position = position;
	m_p_CallBack = callback;
	m_p_PtrObj = ptrObj;

	m_Bounds.x = m_Position.x;
	m_Bounds.y = m_Position.y;
	m_Bounds.w = m_p_Texture->GetWidth();
	m_Bounds.h = m_p_Texture->GetHeight();

	m_Clicked = true;
}

Button::~Button()
{
}

void Button::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, m_p_Texture->GetTexture(), NULL, &m_Bounds);
}

void Button::HandleInput(InputHandler* input)
{
	if(input->MousePressed(input->LeftButton))
	{
		if(!m_Clicked)
		{
			SDL_Rect mouse;
			mouse.x = input->GetMouseX();
			mouse.y = input->GetMouseY();
			mouse.w = 8;
			mouse.h = 8;
			
			m_Clicked = true;

			if(SDL_HasIntersection(&mouse, &m_Bounds))
			{
				m_p_CallBack(m_p_PtrObj);
			}
		}
	}
	else
	{
		m_Clicked = false;
	}
}