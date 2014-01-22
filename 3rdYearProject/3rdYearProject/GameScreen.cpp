#include "GameScreen.h"

GameScreen::GameScreen()
{
}

GameScreen::~GameScreen()
{}

bool GameScreen::IsCovered()
{
	return m_Covered;
}

void GameScreen::SetCovered(bool covered)
{
	m_Covered = covered;
}