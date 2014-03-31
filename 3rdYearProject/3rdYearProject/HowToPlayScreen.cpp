#include "HowToPlayScreen.h"
#include "ScreenManager.h"

HowToPlayScreen::HowToPlayScreen()
{
	m_Covered = false;
}

HowToPlayScreen::~HowToPlayScreen()
{
	delete(m_p_TitleButton);
	delete(m_p_Background);
}

void HowToPlayScreen::Initialize(ScreenManager* manager)
{
	m_p_Manager = manager;
}

void HowToPlayScreen::LoadContent(ContentManager* conMan)
{
	conMan->LoadTexture("HowToPlay.png");
	conMan->LoadTexture("TitleScreenButton.png");
	m_p_Background = new Sprite(conMan->GetTexture("HowToPlay.png"), 800, 640);
	m_p_TitleButton = new Button(conMan->GetTexture("TitleScreenButton.png"), Vector2(0, 0), Wrapper_To_Title,  this);
}

void HowToPlayScreen::UnloadContent()
{
}

void HowToPlayScreen::Update(Uint32 timeElapsed)
{
}

void HowToPlayScreen::Draw(SDL_Renderer* renderer)
{
	m_p_Background->Draw(renderer, Vector2(0, 0));
	m_p_TitleButton->Draw(renderer);
}

void HowToPlayScreen::HandleInput(InputHandler* input)
{
	m_p_TitleButton->HandleInput(input);
}

void HowToPlayScreen::HandleEvents(SDL_Event sdlEvent)
{
}

void HowToPlayScreen::Title()
{
	m_p_Manager->RemoveScreen();
}

void HowToPlayScreen::Wrapper_To_Title(void* ptrObj)
{
	// explicitly cast to a pointer to StartScreen
    HowToPlayScreen* mySelf = (HowToPlayScreen*) ptrObj;

    // call member
    mySelf->Title();
}