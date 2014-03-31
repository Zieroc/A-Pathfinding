#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "GameScreen.h"
#include "Button.h"
#include "GamePlayScreen.h"

class StartScreen : public GameScreen
{
public:
	StartScreen();
	~StartScreen();
	void Initialize(ScreenManager* manager);
	void LoadContent(ContentManager* conMan);
	void UnloadContent();
	void Update(Uint32 timeElapsed);
	void Draw(SDL_Renderer* renderer);
	void HandleInput(InputHandler* input);
	void HandleEvents(SDL_Event sdlEvent);
	void StartGame();
	static void Wrapper_To_Start_Game(void* ptrObj);
	void HowToPlay();
	static void Wrapper_To_How_To_Play(void* ptrObj);
private:
	Button* m_p_StartButton;
	Button* m_p_HowToPlay;
	Sprite* m_p_Background;
};

#endif