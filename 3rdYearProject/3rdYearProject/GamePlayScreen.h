#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H
#include <SDL_ttf.h>
#include "GameScreen.h"
#include "TileMap.h"
#include "InputHandler.h"
#include "LevelMap.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "Action.h"
#include "Button.h"
#include "EnemyFactory.h"

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
	static void Wrapper_To_End_Turn(void* ptrObj);
	void UseAction(Action* action, Character* target);
	CC_Texture* RenderText(const char* message, SDL_Renderer*);
private:
	LevelMap* m_p_Map;
	bool clicked;
	Character* m_p_SelectedPlayer;
	PlayerManager* m_p_PlayerManager;
	EnemyManager* m_p_EnemyManager;
	EnemyFactory* m_p_EnemyFactory;
	int m_Turn;
	Button* m_p_Button;
	Sprite* m_p_ActionMenu;
	Sprite* m_p_Selected; //Temp

	TTF_Font* m_p_Font;
	CC_Texture* m_p_APText;
	CC_Texture* m_p_HealthText;
};

#endif