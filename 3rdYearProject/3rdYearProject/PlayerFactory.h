#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include "Character.h"

class PlayerFactory
{
public:
	PlayerFactory(CC_Texture* sprites[], TileMap* map, SoundManager* soundMan);
	~PlayerFactory();
	Character* CreatePlayer(Vector2 position, int speed);
private:
	TileMap* m_p_Map;
	SoundManager* m_p_SoundMan;
	CC_Texture* m_p_Sprites[MAX_SPRITE];
};

#endif