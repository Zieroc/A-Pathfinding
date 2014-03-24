#include "GameplayScreen.h"
#include <iostream>
#include "ScreenManager.h"

GameplayScreen::GameplayScreen()
{
	m_Covered = false;
	m_Turn = 1;
	pressed = false;
	clicked = false;
}

GameplayScreen::~GameplayScreen()
{
	delete(m_p_Map);
	delete(m_p_EnemyManager);
	delete(m_p_PlayerManager);
}

void GameplayScreen::Initialize(ScreenManager* manager)
{
	m_p_Manager = manager;
}

void GameplayScreen::LoadContent(ContentManager* conMan)
{
	conMan->LoadTexture("Tiles.png");
	conMan->LoadTexture("Guy.png");
	conMan->LoadTexture("Guy2.png");
	m_p_Map = new LevelMap(conMan->GetTexture("Tiles.png"));
	m_p_Map->GenerateMap();
	Sprite* sprites[1];
	Sprite* sprites2[1];
	sprites[0] = new Sprite(conMan->GetTexture("Guy.png"), 32, 32);
	sprites2[0] = new Sprite(conMan->GetTexture("Guy2.png"), 32, 32);

	m_p_Object = new Character(Vector2(32, 96), 128);
	m_p_Object->Initialize(sprites, m_p_Map->GetMap());

	m_p_Object1 = new Character(Vector2(32, 160), 128);
	m_p_Object1->Initialize(sprites, m_p_Map->GetMap());

	m_p_PlayerManager = new PlayerManager();
	m_p_PlayerManager->AddPlayer(m_p_Object);
	m_p_PlayerManager->AddPlayer(m_p_Object1);

	m_p_SelectedPlayer = m_p_Object;

	m_p_Object2 = new Enemy(Vector2(224, 96), 128);
	m_p_Object2->Initialize(sprites2, m_p_Map->GetMap(), m_p_Object);
	m_p_EnemyManager = new EnemyManager();
	m_p_EnemyManager->AddEnemy(m_p_Object2);
}

void GameplayScreen::UnloadContent()
{
}

void GameplayScreen::Update(Uint32 timeElapsed)
{
	m_p_PlayerManager->Update(timeElapsed, m_Turn);
	m_p_EnemyManager->Update(timeElapsed, m_Turn);
}

void GameplayScreen::Draw(SDL_Renderer* renderer)
{
	m_p_Map->Draw(renderer, m_p_Manager->GetCamera());
	m_p_PlayerManager->Draw(renderer, m_p_Manager->GetCamera());
	m_p_EnemyManager->Draw(renderer, m_p_Manager->GetCamera());
}

void GameplayScreen::HandleInput(InputHandler* input)
{
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
			EndTurn();
			pressed = true;
		};
	}
	else
	{
		pressed = false;
	}
	if(input->MousePressed(input->RightButton))
	{
		if(!clicked)
		{
			m_p_SelectedPlayer->SetTarget(Vector2(input->GetMouseX(), input->GetMouseY()));
			clicked = true;
		}
	}
	else
	{
		clicked = false;
	}
	if(input->KeyPressed(SDLK_1))
	{
		m_p_SelectedPlayer = m_p_Object;
	}
	if(input->KeyPressed(SDLK_2))
	{
		m_p_SelectedPlayer = m_p_Object1;
	}
}

void GameplayScreen::HandleEvents(SDL_Event sdlEvent)
{
}

void GameplayScreen::EndTurn()
{
	if(m_Turn == 1)
	{
		m_Turn = 2;
		m_p_EnemyManager->FillAP();
	}
	else
	{
		m_Turn = 1;
		m_p_PlayerManager->FillAP();
	}
}

void GameplayScreen::UseAction(Action* action, Character* target)
{
	if(action->GetType() == 1)
	{
		target->DecHealth(action->GetAmount());
	}
	else
	{
		target->IncHealth(action->GetAmount());
	}
}