#include "GameObject.h"


GameObject::GameObject() : m_Position(Vector2(0, 0)), m_Velocity(Vector2(0, 0)), m_Speed(0)
{
	m_p_Components[0] = new GraphicsComponent(); //Default Graphics Component
	m_p_Components[1] = new PhysicsComponent(); //Default Physics Component
	m_p_Components[2] = new InputComponent(); //Defualt Input Component
	((InputComponent*)m_p_Components[2])->Initialize((PhysicsComponent*)m_p_Components[1]);
}

GameObject::GameObject(Vector2 position, int speed) : m_Velocity(Vector2(0, 0))
{
	m_Position = position;
	m_Speed = speed;
	m_p_Components[0] = new GraphicsComponent(); //Default Graphics Component
	m_p_Components[1] = new PhysicsComponent(); //Default Physics Component
	m_p_Components[2] = new InputComponent(); //Defualt Input Component
	((InputComponent*)m_p_Components[2])->Initialize((PhysicsComponent*)m_p_Components[1]);
}

GameObject::~GameObject()
{
	for(int i = 0; i < MAX_COMPONENTS; i++)
	{
		if(m_p_Components[i] != NULL)
		{
			delete(m_p_Components[i]);
		}
	}
}

void GameObject::Send(int message)
{
	for (int i = 0; i < MAX_COMPONENTS; i++)
    {
      if (m_p_Components[i] != NULL)
      {
        m_p_Components[i]->Receive(message);
      }
    }
}

void GameObject::AddComponent(Component* component, int type)
{
	if(m_p_Components[type] != NULL)
	{
		delete(m_p_Components[type]);
	}

	m_p_Components[type] = component;
}

void GameObject::Initialize(Component* graphics, Component* physics, Component* input)
{
	AddComponent(graphics, 0);
	AddComponent(physics, 1);
	AddComponent(input, 2);
}

void GameObject::InitializeGraphics(Sprite* sprites[])
{
	((GraphicsComponent*)m_p_Components[0])->Initialize(sprites, this);
}

void GameObject::InitializePhysics(TileMap* map)
{
	((PhysicsComponent*)m_p_Components[1])->Initialize(map, this);
}

void GameObject::HandleInput(InputHandler* input)
{
	((InputComponent*)m_p_Components[2])->Update(this, input);
}

void GameObject::Update(Uint32 timeElapsed)
{
	((GraphicsComponent*)m_p_Components[0])->Update(timeElapsed);
	((PhysicsComponent*)m_p_Components[1])->Update(this, timeElapsed);
}


void GameObject::Draw(SDL_Renderer* renderer, Camera* camera)
{
	((GraphicsComponent*)m_p_Components[0])->Draw(this, renderer, camera);
}

Component* GameObject::GetComponent(int type)
{
	return m_p_Components[type];
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
