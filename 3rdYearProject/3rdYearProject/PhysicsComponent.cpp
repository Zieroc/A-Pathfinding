#include "PhysicsComponent.h"
#include "GameObject.h"

PhysicsComponent::PhysicsComponent()
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Initialize()
{
}

void PhysicsComponent::Update(GameObject* gameObject, LevelMap* world)
{
}

void PhysicsComponent::Receive(int message)
{
	DEBUG_MSG("PHYSICS COMPONENT MESSAGE RECIEVED: " + message);
}