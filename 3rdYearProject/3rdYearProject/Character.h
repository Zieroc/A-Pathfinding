#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class Character : public GameObject
{
public:
	Character();
	Character(Vector2 position, int speed);
	virtual ~Character();
	void Initialize(Sprite* sprites[], TileMap* map);
	virtual void Update(Uint32 timeElapsed, int turn);
	virtual void SetTarget(Vector2 target);
	virtual void Move(Uint32 timeElapsed);
	void FillAP();
	void DecreaseAP(int amount);
	void FillHealth();
	void IncHealth(int amount);
	void DecHealth(int amount);
	int GetCurrentAP();
	int GetMaxAP();
	int GetCurrentHealth();
	int GetMaxHealth();
protected:
	void HorizontalTileCollisionTest();
	void VerticalTileCollisionTest();
	virtual	void GetPathNode();

	Vector2 m_Target; //The current tile to move to
	TileMap* m_p_Map;
	bool m_HasReachedTarget;
	bool m_HasPath; // temp
	Pathfinder* m_p_Pathfinder; //Temp
	int m_MaxAP; //Action Points
	int m_CurrentAP;
	int m_MaxHealth;
	int m_CurrentHealth;
};

#endif