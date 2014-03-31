#ifndef HOWTO_SCREEN_H
#define HOWTO_SCREEN_H

#include "GameScreen.h"
#include "Button.h"
#include "GameplayScreen.h"

class HowToPlayScreen : public GameScreen
{
public:
	HowToPlayScreen();
	~HowToPlayScreen();
	void Initialize(ScreenManager* manager);
	void LoadContent(ContentManager* conMan);
	void UnloadContent();
	void Update(Uint32 timeElapsed);
	void Draw(SDL_Renderer* renderer);
	void HandleInput(InputHandler* input);
	void HandleEvents(SDL_Event sdlEvent);
	void Title();
	static void Wrapper_To_Title(void* ptrObj);
private:
	Button* m_p_TitleButton;
	Sprite* m_p_Background;
};

#endif