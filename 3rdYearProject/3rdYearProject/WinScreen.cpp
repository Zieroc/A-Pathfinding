#include "WinScreen.h"
#include "ScreenManager.h"

WinScreen::WinScreen()
{
	m_Covered = false;
}

WinScreen::~WinScreen()
{
	delete(m_p_ExitButton);
	delete(m_p_Background);
}

void WinScreen::Initialize(ScreenManager* manager)
{
	m_p_Manager = manager;
}

void WinScreen::LoadContent(ContentManager* conMan)
{
	conMan->LoadTexture("TitleScreenButton.png");
	conMan->LoadTexture("WinScreen.png");
	m_p_Background = new Sprite(conMan->GetTexture("WinScreen.png"), 800, 640);
	m_p_ExitButton = new Button(conMan->GetTexture("TitleScreenButton.png"), Vector2(0, 0), Wrapper_To_Exit_Game, this);
}

void WinScreen::UnloadContent()
{
}

void WinScreen::Update(Uint32 timeElapsed)
{
}

void WinScreen::Draw(SDL_Renderer* renderer)
{
	m_p_Background->Draw(renderer, Vector2(0, 0));
	m_p_ExitButton->Draw(renderer);
}

void WinScreen::HandleInput(InputHandler* input)
{
	m_p_ExitButton->HandleInput(input);
}

void WinScreen::HandleEvents(SDL_Event sdlEvent)
{
}

void WinScreen::ExitGame()
{
	m_p_Manager->RemoveScreen(); //Return to title
} 

void WinScreen::Wrapper_To_Exit_Game(void* ptrObj)
{
	// explicitly cast to a pointer to StartScreen
    WinScreen* mySelf = (WinScreen*) ptrObj;

    // call member
    mySelf->ExitGame();
}