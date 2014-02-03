#ifndef TEMP_INPUT_COMPONENT_H
#define TEMP_INPUT_COMPONENT_H

#include "Component.h"
#include "InputHandler.h"

#include "InputComponent.h"

class TempInput : public InputComponent
{
public:
	TempInput() {};
	virtual ~TempInput() {};
	virtual void Update(GameObject* gameObject, InputHandler* input);
};

#endif