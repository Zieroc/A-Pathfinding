#include "InputComponent.h"
#include "GameObject.h"


InputComponent::InputComponent() : m_CanSet(true)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::Initialize(PhysicsComponent* physics)
{
	m_Physics = physics;
}

void InputComponent::Update(GameObject* gameObject, InputHandler* input)
{
	if(m_CanSet)
	{
		/*Vector2 pos = gameObject->GetPosition();
		if(input->KeyPressed(SDLK_w))
		{
			pos.y -= 32;
			m_CanSet = false;
			m_Physics->SetTarget(pos);
		}
		else if(input->KeyPressed(SDLK_s))
		{
			pos.y += 32;
			m_CanSet = false;
			m_Physics->SetTarget(pos);
		}
		else if(input->KeyPressed(SDLK_a))
		{
			pos.x -= 32;
			m_CanSet = false;
			m_Physics->SetTarget(pos);
		}
		else if(input->KeyPressed(SDLK_d))
		{
			pos.x += 32;
			m_CanSet = false;
			m_Physics->SetTarget(pos);
		}*/

		if(input->MousePressed(input->LeftButton))
		{
			m_Physics->SetTarget(Vector2(input->GetMouseX(), input->GetMouseY()));
			m_CanSet = false;
		}
	}
}

void InputComponent::Receive(int message)
{
	DEBUG_MSG("INPUT COMPONENT MESSAGE RECIEVED: " + message);
	if(message == 1 || message == 2)
	{
		//m_CanSet = true;
	}
}