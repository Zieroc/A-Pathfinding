#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "Component.h"
#include "InputHandler.h"

class GameObject; //Forward Declaration

class InputComponent : public Component
{
public:
	InputComponent();
	virtual ~InputComponent();
	virtual void Update(GameObject* gameObject, InputHandler* input);
	virtual void Receive(int message);
};

#endif