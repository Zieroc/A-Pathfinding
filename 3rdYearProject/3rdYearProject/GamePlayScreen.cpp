#include "GameplayScreen.h"
#include <iostream>
#include "ScreenManager.h"

//CURRENTLY USED FOR TESTING

GameplayScreen::GameplayScreen()
{
	m_Covered = false;
	pressed = false;
}

GameplayScreen::~GameplayScreen()
{
	delete(m_p_Map);
}

void GameplayScreen::Initialize(ScreenManager* manager)
{
	m_p_Manager = manager;
}

void GameplayScreen::LoadContent(ContentManager* conMan)
{
	conMan->LoadTexture("Tiles.png");
	m_p_Map = new LevelMap(conMan->GetTexture("Tiles.png"));
	m_p_Map->GenerateMap();
}

void GameplayScreen::UnloadContent()
{
}

void GameplayScreen::Update(Uint32 timeElapsed)
{
}

void GameplayScreen::Draw(SDL_Renderer* renderer)
{
	m_p_Map->Draw(renderer, m_p_Manager->GetCamera());
}

void GameplayScreen::HandleInput(InputHandler* input)
{
	if(input->KeyPressed(SDLK_w))
	{
		m_p_Manager->GetCamera()->Move(0, -5);
	}
	if(input->KeyPressed(SDLK_s))
	{
		m_p_Manager->GetCamera()->Move(0, 5);
	}
	if(input->KeyPressed(SDLK_a))
	{
		m_p_Manager->GetCamera()->Move(-5, 0);
	}
	if(input->KeyPressed(SDLK_d))
	{
		m_p_Manager->GetCamera()->Move(5, 0);
	}
	if(input->KeyPressed(SDLK_SPACE))
	{
		if(!pressed)
		{
			m_p_Map->GenerateMap();
			pressed = true;
		}
	}
	else
	{
		pressed = false;
	}
}

void GameplayScreen::HandleEvents(SDL_Event sdlEvent)
{
}
