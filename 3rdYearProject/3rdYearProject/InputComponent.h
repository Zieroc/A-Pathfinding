#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "Component.h"
#include "InputHandler.h"

#include "PhysicsComponent.h"

class GameObject; //Forward Declaration

class InputComponent : public Component
{
public:
	InputComponent();
	virtual ~InputComponent();
	virtual void Initialize(PhysicsComponent* physics);
	virtual void Update(GameObject* gameObject, InputHandler* input);
	virtual void Receive(int message);
protected:
	PhysicsComponent* m_Physics; //Temp
	bool m_CanSet;
};

#endif