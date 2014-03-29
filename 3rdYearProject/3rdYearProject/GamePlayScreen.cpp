#include "GameplayScreen.h"
#include <iostream>
#include "ScreenManager.h"
#include <sstream>

GameplayScreen::GameplayScreen()
{
	m_Covered = false;
	m_Turn = 1;
	clicked = false;
	m_p_APText = NULL;
	m_p_HealthText = NULL;

	
	m_p_PlayerManager = new PlayerManager();
	m_p_EnemyManager = new EnemyManager();
}

GameplayScreen::~GameplayScreen()
{
	delete(m_p_Map);
	delete(m_p_EnemyManager);
	delete(m_p_PlayerManager);
	delete(m_p_EnemyFactory);
	delete(m_p_ActionMenu);
	delete(m_p_Selected);

	delete(m_p_APText);
	delete(m_p_HealthText);
	TTF_CloseFont(m_p_Font);
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
	conMan->LoadTexture("ActionMenu.png");
	conMan->LoadTexture("EndTurn.png");
	conMan->LoadTexture("SelectedCharacter.png");
	m_p_Map = new LevelMap(conMan->GetTexture("Tiles.png"));
	m_p_Map->GenerateMap();
	Sprite* sprites[1];
	Sprite* sprites2[1];
	sprites[0] = new Sprite(conMan->GetTexture("Guy.png"), 32, 32);
	sprites2[0] = new Sprite(conMan->GetTexture("Guy2.png"), 32, 32);

	m_p_ActionMenu = new Sprite(conMan->GetTexture("ActionMenu.png"), 800, 140);
	m_p_Selected = new Sprite(conMan->GetTexture("SelectedCharacter.png"), 36, 36);

	Character* m_p_Object = new Character(Vector2(32, 96), 128);
	m_p_Object->Initialize(sprites, m_p_Map->GetMap());

	Character* m_p_Object1 = new Character(Vector2(32, 160), 128);
	m_p_Object1->Initialize(sprites, m_p_Map->GetMap());

	m_p_PlayerManager->AddPlayer(m_p_Object);
	m_p_PlayerManager->AddPlayer(m_p_Object1);

	m_p_SelectedPlayer = m_p_Object;

	
	m_p_EnemyFactory = new EnemyFactory(m_p_PlayerManager, sprites2, m_p_Map->GetMap());

	m_p_EnemyManager->AddEnemy(m_p_EnemyFactory->CreateEnemy(Vector2(224, 96), 128));
	m_p_EnemyManager->AddEnemy(m_p_EnemyFactory->CreateEnemy(Vector2(224, 160), 128));

	m_p_Button = new Button(conMan->GetTexture("EndTurn.png"), Vector2(400, 520), Wrapper_To_End_Turn, this);

	m_p_Font = TTF_OpenFont("data/Files/SourceSansPro-Semibold.ttf", 16);
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
	Vector2 pos = Vector2(m_p_SelectedPlayer->GetPosition().x - 2, m_p_SelectedPlayer->GetPosition().y - 2);
	m_p_Selected->Draw(renderer, m_p_Manager->GetCamera()->LocationToScreen(pos));
	m_p_ActionMenu->Draw(renderer, Vector2(0, 500));
	m_p_Button->Draw(renderer);

	std::stringstream stream;
	stream.str("");
	stream << "AP: ";
	stream << m_p_SelectedPlayer->GetCurrentAP();

	std::stringstream stream2;
	stream2.str("");
	stream2 << "Health: ";
	stream2 << m_p_SelectedPlayer->GetCurrentHealth();

	if(m_p_APText != NULL)
	{
		delete(m_p_APText);
	}

	if(m_p_HealthText != NULL)
	{
		delete(m_p_HealthText);
	}

	m_p_APText = RenderText(stream.str().c_str(), renderer);
	m_p_HealthText = RenderText(stream2.str().c_str(), renderer);

	SDL_Rect destRect;
	SDL_Rect destRect1;

	destRect.x = 40;
	destRect.y = 540;
	destRect.w = m_p_APText->GetWidth();
	destRect.h = m_p_APText->GetHeight();

	destRect1.x = 40;
	destRect1.y = 580;
	destRect1.w = m_p_HealthText->GetWidth();
	destRect1.h = m_p_HealthText->GetHeight();

	SDL_RenderCopy(renderer, m_p_APText->GetTexture(), NULL, &destRect);
	SDL_RenderCopy(renderer, m_p_HealthText->GetTexture(), NULL, &destRect1);
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
	if(input->MousePressed(input->RightButton))
	{
		if(!clicked)
		{
			Vector2 mousePos = Vector2(input->GetMouseX(), input->GetMouseY());
			m_p_SelectedPlayer->SetTarget(m_p_Manager->GetCamera()->ScreenToLocation(mousePos));
			clicked = true;
		}
	}
	else
	{
		clicked = false;
	}

	m_p_Button->HandleInput(input);
	Character* selected = m_p_PlayerManager->HandleInput(input);

	if(selected != NULL)
	{
		m_p_SelectedPlayer = selected;
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

void GameplayScreen::Wrapper_To_End_Turn(void* ptrObj)
{
    // explicitly cast to a pointer to GameplayScreen
    GameplayScreen* mySelf = (GameplayScreen*) ptrObj;

    // call member
    mySelf->EndTurn();
}

CC_Texture* GameplayScreen::RenderText(const char* message, SDL_Renderer* renderer)
{
	SDL_Color colour;
	colour.a = 255;
	colour.r = 0;
	colour.g = 0;
	colour.b = 0;

	SDL_Surface* surf = TTF_RenderText_Blended(m_p_Font, message, colour);
	if (surf == NULL)
	{
		return NULL;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == NULL)
	{
	
	}

	SDL_FreeSurface(surf);

	CC_Texture* tex = new CC_Texture(texture);
	return tex;
}