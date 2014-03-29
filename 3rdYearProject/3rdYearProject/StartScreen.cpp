#include "StartScreen.h"
#include "ScreenManager.h"

StartScreen::StartScreen()
{
	m_Covered = false;
}

StartScreen::~StartScreen()
{
	delete(m_p_StartButton);
}

void StartScreen::Initialize(ScreenManager* manager)
{
	m_p_Manager = manager;
}

void StartScreen::LoadContent(ContentManager* conMan)
{
	conMan->LoadTexture("StartButton.png");
	m_p_StartButton = new Button(conMan->GetTexture("StartButton.png"), Vector2(200, 200), Wrapper_To_Start_Game, this);
}

void StartScreen::UnloadContent()
{
}

void StartScreen::Update(Uint32 timeElapsed)
{
}

void StartScreen::Draw(SDL_Renderer* renderer)
{
	m_p_StartButton->Draw(renderer);
}

void StartScreen::HandleInput(InputHandler* input)
{
	m_p_StartButton->HandleInput(input);
}

void StartScreen::HandleEvents(SDL_Event sdlEvent)
{
}

void StartScreen::StartGame()
{
	m_p_Manager->AddScreen(new GameplayScreen(), true);
}

void StartScreen::Wrapper_To_Start_Game(void* ptrObj)
{
	// explicitly cast to a pointer to StartScreen
    StartScreen* mySelf = (StartScreen*) ptrObj;

    // call member
    mySelf->StartGame();
}