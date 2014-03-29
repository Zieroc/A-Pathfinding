#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "PlayerManager.h"

class Enemy : public Character
{
public:
	Enemy();
	Enemy(Vector2 position, int speed);
	virtual ~Enemy();
	void Initialize(Sprite* sprites[], TileMap* map, PlayerManager* playerRef);
	virtual void SetTarget(Vector2 target);
	virtual void Update(Uint32 timeElapsed, int turn);
protected:
	virtual void GetPathNode();
	Vector2 m_TargetPlayerPos;
	PlayerManager* m_p_PlayerRef;
};

#endif