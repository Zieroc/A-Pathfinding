#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Component.h"
#include "LevelMap.h"

class GameObject; //Forward Declaration

class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	virtual void Initialize();
	virtual void Update(GameObject* gameObject, LevelMap* world);
	virtual void Receive(int message);
};

#endif