#include "StartScreen.h"
#include "HowToPlayScreen.h"
#include "ScreenManager.h"

StartScreen::StartScreen()
{
	m_Covered = false;
}

StartScreen::~StartScreen()
{
	delete(m_p_StartButton);
	delete(m_p_HowToPlay);
	delete(m_p_Background);
}

void StartScreen::Initialize(ScreenManager* manager)
{
	m_p_Manager = manager;
}

void StartScreen::LoadContent(ContentManager* conMan)
{
	conMan->LoadTexture("StartButton.png");
	conMan->LoadTexture("TitleScreen.png");
	conMan->LoadTexture("HowToPlayButton.png");
	m_p_Background = new Sprite(conMan->GetTexture("TitleScreen.png"), 800, 640);
	m_p_StartButton = new Button(conMan->GetTexture("StartButton.png"), Vector2(0, 290), Wrapper_To_Start_Game, this);
	m_p_HowToPlay = new Button(conMan->GetTexture("HowToPlayButton.png"), Vector2(530, 290), Wrapper_To_How_To_Play, this);
}

void StartScreen::UnloadContent()
{
}

void StartScreen::Update(Uint32 timeElapsed)
{
}

void StartScreen::Draw(SDL_Renderer* renderer)
{
	m_p_Background->Draw(renderer, Vector2(0, 0));
	m_p_StartButton->Draw(renderer);
	m_p_HowToPlay->Draw(renderer);
}

void StartScreen::HandleInput(InputHandler* input)
{
	m_p_HowToPlay->HandleInput(input);
	m_p_StartButton->HandleInput(input);
}

void StartScreen::HandleEvents(SDL_Event sdlEvent)
{
}

void StartScreen::StartGame()
{
	m_p_Manager->AddScreen(new GameplayScreen(), false); //We will always return to start screen so always keep it in memory
}

void StartScreen::Wrapper_To_Start_Game(void* ptrObj)
{
	// explicitly cast to a pointer to StartScreen
    StartScreen* mySelf = (StartScreen*) ptrObj;

    // call member
    mySelf->StartGame();
}

void StartScreen::HowToPlay()
{
	m_p_Manager->AddScreen(new HowToPlayScreen(), false);  //We will always return to start screen so always keep it in memory
}

void StartScreen::Wrapper_To_How_To_Play(void* ptrObj)
{
	// explicitly cast to a pointer to StartScreen
    StartScreen* mySelf = (StartScreen*) ptrObj;

    // call member
    mySelf->HowToPlay();
}