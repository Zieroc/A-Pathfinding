#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include "GameScreen.h"
#include "Button.h"
#include "StartScreen.h"

class WinScreen : public GameScreen
{
public:
	WinScreen();
	~WinScreen();
	void Initialize(ScreenManager* manager);
	void LoadContent(ContentManager* conMan);
	void UnloadContent();
	void Update(Uint32 timeElapsed);
	void Draw(SDL_Renderer* renderer);
	void HandleInput(InputHandler* input);
	void HandleEvents(SDL_Event sdlEvent);
	void ExitGame();
	static void Wrapper_To_Exit_Game(void* ptrObj);
private:
	Button* m_p_ExitButton;
	Sprite* m_p_Background;
};

#endif