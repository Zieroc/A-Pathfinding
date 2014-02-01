#include "InputComponent.h"
#include "GameObject.h"


InputComponent::InputComponent()
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::Update(GameObject* gameObject, InputHandler* input)
{
}

void InputComponent::Receive(int message)
{
	DEBUG_MSG("INPUT COMPONENT MESSAGE RECIEVED: " + message);
}