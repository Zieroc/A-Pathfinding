#include "LoseScreen.h"
#include "ScreenManager.h"

LoseScreen::LoseScreen()
{
	m_Covered = false;
}

LoseScreen::~LoseScreen()
{
	delete(m_p_ExitButton);
	delete(m_p_Background);
}

void LoseScreen::Initialize(ScreenManager* manager)
{
	m_p_Manager = manager;
}

void LoseScreen::LoadContent(ContentManager* conMan)
{
	conMan->LoadTexture("TitleScreenButton.png");
	conMan->LoadTexture("LoseScreen.png");
	m_p_Background = new Sprite(conMan->GetTexture("LoseScreen.png"), 800, 640);
	m_p_ExitButton = new Button(conMan->GetTexture("TitleScreenButton.png"), Vector2(0, 0), Wrapper_To_Exit_Game, this);
}

void LoseScreen::UnloadContent()
{
}

void LoseScreen::Update(Uint32 timeElapsed)
{
}

void LoseScreen::Draw(SDL_Renderer* renderer)
{
	m_p_Background->Draw(renderer, Vector2(0, 0));
	m_p_ExitButton->Draw(renderer);
}

void LoseScreen::HandleInput(InputHandler* input)
{
	m_p_ExitButton->HandleInput(input);
}

void LoseScreen::HandleEvents(SDL_Event sdlEvent)
{
}

void LoseScreen::ExitGame()
{
	m_p_Manager->RemoveScreen(); // Return to Title
}

void LoseScreen::Wrapper_To_Exit_Game(void* ptrObj)
{
	// explicitly cast to a pointer to StartScreen
    LoseScreen* mySelf = (LoseScreen*) ptrObj;

    // call member
    mySelf->ExitGame();
}