#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Component.h"
#include "TileMap.h"
#include "Vector2.h"
#include "Pathfinder.h" //Temp

class GameObject; //Forward Declaration

class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	virtual void Initialize(TileMap* map, GameObject* gmaeObject);
	virtual void Update(GameObject* gameObject, Uint32 timeElapsed);
	virtual void Receive(int message);
	void SetTarget(Vector2 target);
protected:
	Vector2 m_Target; //The current tile to move to
	TileMap* m_p_Map;
	void HorizontalTileCollisionTest(GameObject* gameObject);
	void VerticalTileCollisionTest(GameObject* gameObject);
	bool m_HasReachedTarget;

	bool m_HasPath; // temp
	Pathfinder* m_p_Pathfinder; //Temp
};

#endif