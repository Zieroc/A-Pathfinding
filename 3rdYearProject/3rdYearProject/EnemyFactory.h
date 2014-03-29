#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "Enemy.h"

class EnemyFactory
{
public:
	EnemyFactory(PlayerManager* playerRef, Sprite* sprites[], TileMap* map);
	~EnemyFactory();
	Enemy* CreateEnemy(Vector2 position, int speed);
private:
	PlayerManager* m_p_PlayerRef;
	TileMap* m_p_Map;
	Sprite* m_p_Sprites[MAX_SPRITE];
};

#endif