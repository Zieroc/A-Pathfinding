#include "Game.h"
#include <iostream>


Game::Game()
{
	m_Running = true;
}

Game::~Game()
{
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
		}
		else
		{
			DEBUG_MSG("Window Creation Failed");
			return false;
		}
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
	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
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
}

bool Game::IsRunning()
{
	return m_Running;
}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
	m_Running = false;
}