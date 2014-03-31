#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "Enemy.h"

class EnemyFactory
{
public:
	EnemyFactory(PlayerManager* playerRef, CC_Texture* sprites[], TileMap* map, SoundManager* soundMan);
	~EnemyFactory();
	Enemy* CreateEnemy(Vector2 position, int speed);
private:
	PlayerManager* m_p_PlayerRef;
	TileMap* m_p_Map;
	SoundManager* m_p_SoundMan;
	CC_Texture* m_p_Sprites[MAX_SPRITE];
};

#endif