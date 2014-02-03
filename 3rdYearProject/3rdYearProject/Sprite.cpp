#include "Sprite.h"
#include <iostream>

Sprite::Sprite(CC_Texture* texture, int width, int height)
{
	m_p_Texture = texture;

	m_DestinationRect.w = width;
	m_DestinationRect.h = height;

	m_SourceRect.w = width;
	m_SourceRect.h = height;

	m_Columns = texture->GetWidth() / width;
	m_Rows = texture->GetHeight() / height;

	m_Timer = 0;
	m_Interval = 100;

	m_Animate = true;
	m_Looping = true;

	m_NumStates = 1;
	m_CurrentState = 0;
}

Sprite::~Sprite()
{
}

void Sprite::Update(Uint32 timeElapsed)
{
	if (m_Animate && m_CurrentState < m_NumStates)
	{
		m_Timer += timeElapsed;
		//Check the timer is more than the chosen interval
		if (m_Timer >= m_Interval)
		{
			//Show the next frame
			m_CurrentState++;
			//Reset the timer
			m_Timer = 0;
		}
	}

	if (m_CurrentState >= m_NumStates)
    {
        if (m_Looping)
        {
            m_CurrentState = 0;   //Animation should loop so set currentState back to 0
        }
        else
        {
            m_CurrentState--;     //Animation has reached end so drop back one so the image can be drawn
        }
    }
}

void Sprite::Draw(SDL_Renderer* renderer, Vector2 position, Camera* camera)
{
	m_DestinationRect.x = position.x;
	m_DestinationRect.y = position.y;

	m_SourceRect.x = m_SourceRect.w * (m_CurrentState % m_Columns);
    m_SourceRect.y = m_SourceRect.h * (m_CurrentState/ m_Columns);

	SDL_RenderCopy(renderer, m_p_Texture->GetTexture(), &m_SourceRect, &m_DestinationRect);
}

CC_Texture* Sprite::GetTexture()
{
	return m_p_Texture;
}