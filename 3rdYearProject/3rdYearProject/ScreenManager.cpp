#include "ScreenManager.h"
#include <iostream>


ScreenManager::ScreenManager(SDL_Renderer* renderer, ContentManager* conMan, Camera* camera)
{
	m_p_Renderer = renderer;
	m_p_ContentManager = conMan;
	m_p_Camera = camera;
	m_p_InputHandler = new InputHandler();
}

ScreenManager::~ScreenManager()
{
	while(!m_p_Screens.empty())
	{
		//Unload any content held by that screen
		m_p_Screens.front()->UnloadContent();
		delete(m_p_Screens.front());
		m_p_Screens.pop_front();
	}

	delete(m_p_InputHandler);
}

void ScreenManager::Initialize()
{
}

void ScreenManager::LoadContent()
{
	m_p_Screens.front()->LoadContent(m_p_ContentManager);
}

void ScreenManager::UnloadContent()
{
	m_p_Screens.front()->UnloadContent();
}

void ScreenManager::Update(Uint32 timeElapsed)
{
	//m_p_InputHandler->Update(); //Update the input

	m_p_UpdateScreens.clear();

	for(auto iter = m_p_Screens.begin(); iter != m_p_Screens.end(); ++iter)
	{
		if(iter != m_p_Screens.end())
		{
			m_p_UpdateScreens.push_front(*iter);
		}
	}

    while (!m_p_UpdateScreens.empty())
    {
        //Get the screen and the remove it from the update list
        GameScreen* screen = m_p_UpdateScreens.front();
        m_p_UpdateScreens.pop_front();

        // Update the screen.
        screen->Update(timeElapsed);
	}

	m_p_Screens.front()->HandleInput(m_p_InputHandler);
}

void ScreenManager::HandleEvents(SDL_Event sdlEvent)
{
	//Front screen will always be the active one
	m_p_Screens.front()->HandleEvents(sdlEvent);
}

void ScreenManager::Draw()
{
	for(forward_list<GameScreen*>::const_iterator iter = m_p_Screens.begin(); iter != m_p_Screens.end(); ++iter)
	{
		if(!(*iter)->IsCovered())
		{
			(*iter)->Draw(m_p_Renderer);
		}
	}
}

void ScreenManager::AddScreen(GameScreen* screen, bool removePrevious)
{
	if(removePrevious)
	{
		RemoveScreen();
	}

	if(!m_p_Screens.empty())
	{
		m_p_Screens.front()->SetCovered(true);
	}

	screen->Initialize(this);
	screen->LoadContent(m_p_ContentManager);
	m_p_Screens.push_front(screen);
}

void ScreenManager::AddPopup(GameScreen* popup)
{
	popup->Initialize(this);
	popup->LoadContent(m_p_ContentManager);
	m_p_Screens.push_front(popup);
}

void ScreenManager::RemoveScreen()
{
	if(!m_p_Screens.empty())
	{
		m_p_Screens.front()->UnloadContent();
		delete(m_p_Screens.front());
		m_p_Screens.pop_front();
		if(!m_p_Screens.empty())
		{
			m_p_Screens.front()->SetCovered(false);
		}
	}
}

Camera* ScreenManager::GetCamera()
{
	return m_p_Camera;
}

bool ScreenManager::GetRunning()
{
	return m_Running;
}

void ScreenManager::SetRunning(bool running)
{
	m_Running = running;
}