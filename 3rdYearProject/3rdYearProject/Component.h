#ifndef COMPONENT_H
#define COMPONENT_H

#include "Debug.h"
#include <iostream>

class Component
{
public:
	virtual ~Component() {}
	virtual void Receive(int message) = 0;
};

#endif