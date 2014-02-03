#include "GameplayScreen.h"
#include <iostream>
#include "ScreenManager.h"

//CURRENTLY USED FOR TESTING
#include "TempInput.h"

GameplayScreen::GameplayScreen()
{
	m_Covered = false;
	pressed = false;
}

GameplayScreen::~GameplayScreen()
{
	delete(m_p_Map);
	delete(m_p_Object);
}

void GameplayScreen::Initialize(ScreenManager* manager)
{
	m_p_Manager = manager;
}

void GameplayScreen::LoadContent(ContentManager* conMan)
{
	conMan->LoadTexture("Tiles.png");
	conMan->LoadTexture("Guy.png");
	m_p_Map = new LevelMap(conMan->GetTexture("Tiles.png"));
	m_p_Map->GenerateMap();
	Sprite* sprites[1];
	sprites[0] = new Sprite(conMan->GetTexture("Guy.png"), 32, 32);
	m_p_Object = new GameObject(Vector2(32, 96), 128);
	m_p_Object->InitializeGraphics(sprites);
	m_p_Object->InitializePhysics(m_p_Map->GetMap());
}

void GameplayScreen::UnloadContent()
{
}

void GameplayScreen::Update(Uint32 timeElapsed)
{
	m_p_Object->Update(timeElapsed);
}

void GameplayScreen::Draw(SDL_Renderer* renderer)
{
	m_p_Map->Draw(renderer, m_p_Manager->GetCamera());
	m_p_Object->Draw(renderer, m_p_Manager->GetCamera());
}

void GameplayScreen::HandleInput(InputHandler* input)
{
	m_p_Object->HandleInput(input);

	if(input->KeyPressed(SDLK_UP))
	{
		m_p_Manager->GetCamera()->Move(Vector2(0, -5));
	}
	if(input->KeyPressed(SDLK_DOWN))
	{
		m_p_Manager->GetCamera()->Move(Vector2(0, 5));
	}
	if(input->KeyPressed(SDLK_LEFT))
	{
		m_p_Manager->GetCamera()->Move(Vector2(-5, 0));
	}
	if(input->KeyPressed(SDLK_RIGHT))
	{
		m_p_Manager->GetCamera()->Move(Vector2(5, 0));
	}
	if(input->KeyPressed(SDLK_SPACE))
	{
		if(!pressed)
		{
			/*m_p_Map->GenerateMap();*/
			TempInput* inputC = new TempInput();
			inputC->Initialize((PhysicsComponent*)m_p_Object->GetComponent(1));
			m_p_Object->AddComponent(inputC, 2);

			pressed = true;
		}
	}
	else
	{
		pressed = false;
	}
	if(input->KeyPressed(SDLK_LSHIFT))
	{
		InputComponent* inputC = new InputComponent();
		inputC->Initialize((PhysicsComponent*)m_p_Object->GetComponent(1));
		m_p_Object->AddComponent(inputC, 2);
	}
}

void GameplayScreen::HandleEvents(SDL_Event sdlEvent)
{
}
