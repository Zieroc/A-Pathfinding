#include "Camera.h"


Camera::Camera(float x, float y, float  width, float height, SDL_Rect levelRect)
{
	m_PositionX = x;
	m_PositionY = y;
	m_ViewPortW = width;
	m_ViewPortH = height;
	m_LevelRectangle = levelRect;
}


Camera::~Camera()
{
}

void Camera::Move(float x, float y)
{
	float newPosX = m_PositionX + x;
	float newPosY = m_PositionY + y;

	if(newPosX < 0)
	{
		newPosX = 0;
	}
	else if(newPosX > m_LevelRectangle.w - m_ViewPortW)
	{
		newPosX = m_LevelRectangle.w - m_ViewPortW;
	}
	if(newPosY < 0)
	{
		newPosY = 0;
	}
	else if(newPosY > m_LevelRectangle.h - m_ViewPortH)
	{
		newPosY = m_LevelRectangle.h - m_ViewPortH;
	}

	m_PositionX = newPosX;
	m_PositionY = newPosY;
}

bool Camera::IsObjectVisible(SDL_Rect objectBounds)
{
	SDL_Rect viewPort;
	viewPort.x = m_PositionX;
	viewPort.y = m_PositionY;
	viewPort.w = m_ViewPortW;
	viewPort.h = m_ViewPortH;

	return SDL_HasIntersection(&viewPort, &objectBounds);
}

float Camera::XLocationToScreen(float Xlocation)
{
	Xlocation -= m_PositionX;
	return Xlocation;
}

float Camera::YLocationToScreen(float Ylocation)
{
	Ylocation -= m_PositionY;
	return Ylocation;
}

SDL_Rect Camera::LocationToScreen(SDL_Rect location)
{
	location.x -= (int)m_PositionX;
	location.y -= (int)m_PositionY;
	return location;
}

float Camera::XScreenToLocation(float Xlocation)
{
	Xlocation += m_PositionX;
	return Xlocation;
}

float Camera::YScreenToLocation(float Ylocation)
{
	Ylocation += m_PositionY;
	return Ylocation;
}

SDL_Rect Camera::ScreenToLocation(SDL_Rect location)
{
	location.x += (int)m_PositionX;
	location.y += (int)m_PositionY;
	return location;
}

float Camera::GetPositionX()
{
	return m_PositionX;
}

float Camera::GetPositionY()
{
	return m_PositionY;
}

float Camera::GetViewPortW()
{
	return m_ViewPortW;
}

float Camera::GetViewPortH()
{
	return m_ViewPortH;
}

void Camera::CalcViewPort(float amount)
{
	m_ViewPortW *= amount;
	m_ViewPortH *= amount;
}