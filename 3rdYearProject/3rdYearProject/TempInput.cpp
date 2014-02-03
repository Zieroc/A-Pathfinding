#include "TempInput.h"
#include "GameObject.h"

void TempInput::Update(GameObject* gameObject, InputHandler* input)
{
	if(m_CanSet)
	{
		Vector2 pos = gameObject->GetPosition();
		if(input->KeyPressed(SDLK_w))
		{
			pos.y += 32;
			m_CanSet = false;
			m_Physics->SetTarget(pos);
		}
		else if(input->KeyPressed(SDLK_s))
		{
			pos.y -= 32;
			m_CanSet = false;
			m_Physics->SetTarget(pos);
		}
		else if(input->KeyPressed(SDLK_a))
		{
			pos.x += 32;
			m_CanSet = false;
			m_Physics->SetTarget(pos);
		}
		else if(input->KeyPressed(SDLK_d))
		{
			pos.x -= 32;
			m_CanSet = false;
			m_Physics->SetTarget(pos);
		}
	}
}