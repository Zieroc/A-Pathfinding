#include "GameObject.h"


GameObject::GameObject() : m_Position(Vector2(0, 0)), m_Velocity(Vector2(0, 0)), m_Speed(0)
{
	CalcBounds();
}

GameObject::GameObject(Vector2 position, int speed) : m_Velocity(Vector2(0, 0))
{
	m_Position = position;
	m_Speed = speed;
	CalcBounds();
}

GameObject::~GameObject()
{
	for(int i = 0; i < MAX_SPRITE; i++)
	{
		if(m_p_Sprites[i] != NULL)
		{
			delete(m_p_Sprites[i]);
		}
	}
}

void GameObject::Initialize(Sprite* sprites[])
{
	for(int i = 0; i < MAX_SPRITE; i++)
	{
		if(m_p_Sprites[i] != NULL)
		{
			m_p_Sprites[i] = sprites[i];
		}
	}

	m_p_CurrentSprite = m_p_Sprites[0];
	SetBounds(m_p_CurrentSprite->GetTexture()->GetWidth(), m_p_CurrentSprite->GetTexture()->GetHeight());
}

void GameObject::Update(Uint32 timeElapsed)
{
	m_p_CurrentSprite->Update(timeElapsed);
}


void GameObject::Draw(SDL_Renderer* renderer, Camera* camera)
{
	m_p_CurrentSprite->Draw(renderer, camera->LocationToScreen(GetPosition()), camera);
}

Vector2 GameObject::GetPosition()
{
	return m_Position;
}

Vector2 GameObject::GetVelocity()
{
	return m_Velocity;
}

int GameObject::GetSpeed()
{
	return m_Speed;
}

SDL_Rect GameObject::GetBounds()
{
	return m_Bounds;
}

void GameObject::SetPosition(Vector2 position)
{
	m_Position = position;
}

void GameObject::SetVelocity(Vector2 velocity)
{
	m_Velocity = velocity;
}

void GameObject::SetSpeed(int speed)
{
	m_Speed = speed;
}

void GameObject::SetBounds(int width, int height)
{
	m_Bounds.w = width;
	m_Bounds.h = height;
}

void GameObject::CalcBounds()
{
	m_Bounds.x = m_Position.x;
	m_Bounds.y = m_Position.y;
}