#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H
#include <SDL_ttf.h>
#include "GameScreen.h"
#include "TileMap.h"
#include "InputHandler.h"
#include "LevelManager.h"
#include "Button.h"

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
	void Attack(); //1 Player Attack, 2 Enemy Attack
	static void Wrapper_To_Attack(void* ptrObj);
	CC_Texture* RenderText(const char* message, SDL_Renderer*);
private:
	LevelManager* m_p_LevelManager;
	Button* m_p_EndTurnButton;
	Button* m_p_AttackButton;
	Sprite* m_p_ActionMenu;
	Sprite* m_p_Selected;
	SoundManager* m_p_SoundManager;
	Character* m_p_SelectedPlayer;
	int m_Turn;
	TTF_Font* m_p_Font;
	CC_Texture* m_p_APText;
	CC_Texture* m_p_HealthText;
};

#endif