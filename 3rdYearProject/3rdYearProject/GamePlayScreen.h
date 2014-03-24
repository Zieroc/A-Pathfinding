#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H
#include "GameScreen.h"
#include "TileMap.h"
#include "InputHandler.h"
#include "LevelMap.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "Action.h"

class GameplayScreen : public GameScreen
{
public:
	GameplayScreen();
	~GameplayScreen();
	void Initialize(ScreenManager* manager);
	void LoadContent(ContentManager* conMan);
	void UnloadContent();
	void Update(Uint32 timeElapsed);
	void Draw(SDL_Renderer* renderer);
	void HandleInput(InputHandler* input);
	void HandleEvents(SDL_Event sdlEvent);
	void EndTurn();
	void UseAction(Action* action, Character* target);
private:
	LevelMap* m_p_Map;
	bool pressed;
	bool clicked;
	Character* m_p_SelectedPlayer;
	Character* m_p_Object;
	Character* m_p_Object1;
	Enemy* m_p_Object2;
	PlayerManager* m_p_PlayerManager;
	EnemyManager* m_p_EnemyManager;
	int m_Turn;
};

#endif