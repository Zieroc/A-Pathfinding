#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(PlayerManager* playerRef, CC_Texture* sprites[], TileMap* map, SoundManager* soundMan)
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
	m_p_SoundMan = soundMan;
}

EnemyFactory::~EnemyFactory()
{
}

Enemy* EnemyFactory::CreateEnemy(Vector2 position, int speed)
{
	Enemy* enemy = new Enemy(position, speed);
	Sprite* sprites[MAX_SPRITE];

	sprites[0] = new Sprite(m_p_Sprites[0], 32, 32);
	sprites[1] = new Sprite(m_p_Sprites[1], 46, 40, false);

	enemy->Initialize(sprites, m_p_Map, m_p_PlayerRef, m_p_SoundMan);
	return enemy;
}