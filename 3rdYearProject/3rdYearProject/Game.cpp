#include "Game.h"
#include <iostream>


Game::Game()
{
	m_Running = true;
	m_p_ScreenManager = NULL;
	m_LastTime = SDL_GetTicks();
	m_p_ContentManager = NULL;
}

Game::~Game()
{
	delete(m_p_ScreenManager);
	delete(m_p_ContentManager);
	//delete(m_p_Camera);
}

bool Game::Initialize(const char* title, int x, int y, int width, int height, int flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		DEBUG_MSG("Initialised");
		m_p_Window = SDL_CreateWindow(title, x, y, width, height, flags);
		
		if(m_p_Window != 0)
		{
			DEBUG_MSG("Window Created");
			m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, SDL_RENDERER_ACCELERATED);

			if(m_p_Renderer != 0)
			{
				DEBUG_MSG("Renderer Created");
				SDL_SetRenderDrawColor(m_p_Renderer, 255, 255, 255, 255);
				SDL_RenderSetLogicalSize(m_p_Renderer, width, height);
			}
			else
			{
				DEBUG_MSG("Renderer Creation Failed");
				return false;
			}

			//Initialise SDL_mixer
			if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
			{
				DEBUG_MSG("Audio Initialisation Failed");
				return false; 
			}
		}
		else
		{
			DEBUG_MSG("Window Creation Failed");
			return false;
		}

		m_p_ContentManager = new ContentManager(m_p_Renderer);
		m_p_ScreenManager = new ScreenManager(m_p_Renderer, m_p_ContentManager);
		return true;
	}
	else
	{
		DEBUG_MSG("Initialisation Failed");
		return false;
	}
}

void Game::Draw()
{
	SDL_RenderClear(m_p_Renderer);
	m_p_ScreenManager->Draw();
	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
	m_p_ScreenManager->Update(GetTimeElapsed());
	m_LastTime = SDL_GetTicks(); //Update time
}

void Game::HandleEvents()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			m_Running = false;
			break;
		default:
			break;
		}
	}

	m_p_ScreenManager->HandleEvents(event); // If it isn't an main event let the screens handle it
}

bool Game::IsRunning()
{
	return m_Running;
}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	Mix_CloseAudio();
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
	m_Running = false;
}

Uint32 Game::GetTimeElapsed()
{
	return SDL_GetTicks() - m_LastTime;
}