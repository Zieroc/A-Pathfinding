#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(PlayerManager* playerRef, Sprite* sprites[], TileMap* map)
{
	m_p_PlayerRef = playerRef;
	for(int i = 0; i < MAX_SPRITE; i++)
	{
		if(m_p_Sprites[i] != NULL)
		{
			m_p_Sprites[i] = sprites[i];
		}
	}
	m_p_Map = map;
}

EnemyFactory::~EnemyFactory()
{
}

Enemy* EnemyFactory::CreateEnemy(Vector2 position, int speed)
{
	Enemy* enemy = new Enemy(position, speed);
	enemy->Initialize(m_p_Sprites, m_p_Map, m_p_PlayerRef);
	return enemy;
}