#include "GraphicsComponent.h"
#include "GameObject.h"

GraphicsComponent::GraphicsComponent()
{
}

GraphicsComponent::~GraphicsComponent()
{
	for(int i = 0; i < MAX_SPRITE; i++)
	{
		if(m_p_Sprites[i] != NULL)
		{
			delete(m_p_Sprites[i]);
		}
	}
}

void GraphicsComponent::Initialize(Sprite* sprites[], GameObject* gameObject)
{
	//If too many sprites were passed in just ignore them
	for(int i = 0; i < MAX_SPRITE; i++)
	{
		if(m_p_Sprites[i] != NULL)
		{
			m_p_Sprites[i] = sprites[i];
		}
	}

	m_p_CurrentSprite = m_p_Sprites[0];
	gameObject->SetBounds(m_p_CurrentSprite->GetTexture()->GetWidth(), m_p_CurrentSprite->GetTexture()->GetHeight());
}

void GraphicsComponent::Update(Uint32 timeElapsed)
{
	m_p_CurrentSprite->Update(timeElapsed);
}

void GraphicsComponent::Draw(GameObject* gameObject, SDL_Renderer* renderer, Camera* camera)
{
	m_p_CurrentSprite->Draw(renderer, camera->LocationToScreen(gameObject->GetPosition()), camera);
}

void GraphicsComponent::Receive(int message)
{
	DEBUG_MSG("GRAPHICS COMPONENT MESSAGE RECIEVED: " + message);
}