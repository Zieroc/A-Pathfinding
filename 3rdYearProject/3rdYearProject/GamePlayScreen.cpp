#include "GameplayScreen.h"
#include <iostream>
#include "ScreenManager.h"
#include <sstream>
#include "WinScreen.h"
#include "LoseScreen.h"

GameplayScreen::GameplayScreen()
{
	m_Covered = false;
	m_Turn = 1;
	m_p_APText = NULL;
	m_p_HealthText = NULL;

	m_p_LevelManager = new LevelManager();
}

GameplayScreen::~GameplayScreen()
{
	delete(m_p_ActionMenu);
	delete(m_p_Selected);
	delete(m_p_LevelManager);
	delete(m_p_SoundManager);
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
	m_p_SoundManager = new SoundManager(conMan);
	conMan->LoadTexture("Tiles.png");
	conMan->LoadTexture("Knight.png");
	conMan->LoadTexture("KnightAttack.png");
	conMan->LoadTexture("Goblin.png");
	conMan->LoadTexture("GoblinAttack.png");
	conMan->LoadTexture("ActionMenu.png");
	conMan->LoadTexture("EndTurn.png");
	conMan->LoadTexture("Attack.png");
	conMan->LoadTexture("SelectedCharacter.png");
	conMan->LoadSoundEffect("hit.wav");
	CC_Texture* sprites[2];
	CC_Texture* sprites2[2];
	sprites[0] = conMan->GetTexture("Knight.png");
	sprites[1] = conMan->GetTexture("KnightAttack.png");
	sprites2[0] = conMan->GetTexture("Goblin.png");
	sprites2[1] = conMan->GetTexture("GoblinAttack.png");

	m_p_ActionMenu = new Sprite(conMan->GetTexture("ActionMenu.png"), 800, 140);
	m_p_Selected = new Sprite(conMan->GetTexture("SelectedCharacter.png"), 36, 36);

	m_p_LevelManager->Initialize(sprites2, sprites, conMan->GetTexture("Tiles.png"), m_p_Manager->GetCamera(), m_p_SoundManager);
	m_p_SelectedPlayer = m_p_LevelManager->GenerateLevel();

	m_p_EndTurnButton = new Button(conMan->GetTexture("EndTurn.png"), Vector2(600, 520), Wrapper_To_End_Turn, this);
	m_p_AttackButton = new Button(conMan->GetTexture("Attack.png"), Vector2(400, 520), Wrapper_To_Attack, this);

	m_p_Font = TTF_OpenFont("data/Files/SourceSansPro-Semibold.ttf", 16);
}

void GameplayScreen::UnloadContent()
{
}

void GameplayScreen::Update(Uint32 timeElapsed)
{
	if(m_p_SelectedPlayer == NULL)
	{
		if(!m_p_LevelManager->GetPlayerManager()->GetPlayers().empty())
		{
			m_p_SelectedPlayer = m_p_LevelManager->GetPlayerManager()->GetPlayer(0);
		}
	}
	m_p_LevelManager->Update(timeElapsed, m_Turn);

	if(m_Turn == 2)
	{
		if(m_p_LevelManager->GetEnemyManager()->TurnComplete())
		{
			EndTurn();
		}
	}

	if(m_p_LevelManager->GetEnemyManager()->GetEnemies().empty())
	{
		m_p_Manager->AddScreen(new WinScreen(), true);
	}
	else if(m_p_LevelManager->GetPlayerManager()->GetPlayers().empty())
	{
		m_p_Manager->AddScreen(new LoseScreen(), true);
	}
}

void GameplayScreen::Draw(SDL_Renderer* renderer)
{
	m_p_LevelManager->Draw(renderer);

	if(m_p_SelectedPlayer != NULL && m_Turn == 1)
	{
		Vector2 pos = Vector2(m_p_SelectedPlayer->GetPosition().x - 2, m_p_SelectedPlayer->GetPosition().y - 2);
		m_p_Selected->Draw(renderer, m_p_Manager->GetCamera()->LocationToScreen(pos));
	}

	m_p_ActionMenu->Draw(renderer, Vector2(0, 500));
	if(m_Turn == 1)
	{
		
		m_p_EndTurnButton->Draw(renderer);
		m_p_AttackButton->Draw(renderer);

		if(m_p_SelectedPlayer != NULL)
		{
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
	}
}

void GameplayScreen::HandleInput(InputHandler* input)
{
	if(input->KeyPressed(SDLK_UP))
	{
		m_p_Manager->GetCamera()->Move(Vector2(0, -15));
	}
	if(input->KeyPressed(SDLK_DOWN))
	{
		m_p_Manager->GetCamera()->Move(Vector2(0, 15));
	}
	if(input->KeyPressed(SDLK_LEFT))
	{
		m_p_Manager->GetCamera()->Move(Vector2(-15, 0));
	}
	if(input->KeyPressed(SDLK_RIGHT))
	{
		m_p_Manager->GetCamera()->Move(Vector2(15, 0));
	}
	
	if(m_Turn == 1)
	{
		Character* selected = m_p_LevelManager->HandleInput(input,  m_p_SelectedPlayer);

		if(selected != NULL)
		{
			m_p_SelectedPlayer = selected;
		}

		if(m_Turn == 1)
		{
			m_p_EndTurnButton->HandleInput(input);
			m_p_AttackButton->HandleInput(input);
		}
	}
}

void GameplayScreen::HandleEvents(SDL_Event sdlEvent)
{
}

void GameplayScreen::EndTurn()
{
	if(m_Turn == 1)
	{
		m_p_SelectedPlayer = m_p_LevelManager->GetPlayerManager()->GetPlayer(0);
		m_Turn = 2;
		m_p_LevelManager->FillAP(1);
	}
	else
	{
		m_p_SelectedPlayer = m_p_LevelManager->GetPlayerManager()->GetPlayer(0);
		m_Turn = 1;
		m_p_LevelManager->FillAP(2);
	}
}

void GameplayScreen::Wrapper_To_End_Turn(void* ptrObj)
{
    // explicitly cast to a pointer to GameplayScreen
    GameplayScreen* mySelf = (GameplayScreen*) ptrObj;

    // call member
    mySelf->EndTurn();
}

void GameplayScreen::Attack()
{
	if(m_p_SelectedPlayer->GetCurrentAP() > 0)
	{
		
		int attack = m_p_SelectedPlayer->GetCurrentAP();
		m_p_SelectedPlayer->DecreaseAP(attack);
		m_p_SelectedPlayer->SwitchAnimation(1);

		for(int i = 0; i < m_p_LevelManager->GetEnemyManager()->GetEnemies().size(); i++)
		{
			if(m_p_SelectedPlayer->GetPosition().DistanceTo(m_p_LevelManager->GetEnemyManager()->GetEnemy(i)->GetPosition()) == 32)
			{
				m_p_LevelManager->GetEnemyManager()->GetEnemy(i)->DecHealth(attack);
			}
		}
	}
}

void GameplayScreen::Wrapper_To_Attack(void* ptrObj)
{
	 GameplayScreen* mySelf = (GameplayScreen*) ptrObj;

    // call member
    mySelf->Attack();
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