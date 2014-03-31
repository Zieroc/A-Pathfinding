#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "LevelMap.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "EnemyFactory.h"
#include "PlayerFactory.h"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();
	void Initialize(CC_Texture* enemySprites[], CC_Texture* playerSprites[], CC_Texture* tiles, Camera* camera, SoundManager* soundMan);
	Character* GenerateLevel();
	void Update(Uint32 timeElapsed, int turn);
	void Draw(SDL_Renderer* renderer);
	Character* HandleInput(InputHandler* input, Character* selectedPlayer);
	void FillAP(int i);
	PlayerManager* GetPlayerManager();
	EnemyManager* GetEnemyManager();
private:
	LevelMap* m_p_Map;
	PlayerManager* m_p_PlayerManager;
	EnemyManager* m_p_EnemyManager;
	EnemyFactory* m_p_EnemyFactory;
	PlayerFactory* m_p_PlayerFactory;
	bool m_Clicked;
	Camera* m_p_Camera;
};

#endif