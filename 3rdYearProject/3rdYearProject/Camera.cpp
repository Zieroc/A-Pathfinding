#include "Camera.h"


Camera::Camera(Vector2 pos, Vector2 size, SDL_Rect levelRect)
{
	m_Position = pos;
	m_ViewPortSize = size;
	m_LevelRectangle = levelRect;
}

Camera::~Camera()
{
}

void Camera::Move(Vector2 amount)
{
	Vector2 newPos = m_Position + amount;

	newPos.Clamp(Vector2(m_LevelRectangle.x, m_LevelRectangle.y), Vector2(m_LevelRectangle.w - m_ViewPortSize.x, m_LevelRectangle.h - m_ViewPortSize.y));

	m_Position = newPos;
}

bool Camera::IsObjectVisible(SDL_Rect objectBounds)
{
	SDL_Rect viewPort;
	viewPort.x = m_Position.x;
	viewPort.y = m_Position.y;
	viewPort.w = m_ViewPortSize.x;
	viewPort.h = m_ViewPortSize.y;

	return SDL_HasIntersection(&viewPort, &objectBounds);
}

Vector2 Camera::LocationToScreen(Vector2 location)
{
	location -= m_Position;
	return location;
}

SDL_Rect Camera::LocationToScreen(SDL_Rect location)
{
	location.x -= (int)m_Position.x;
	location.y -= (int)m_Position.y;
	return location;
}

Vector2 Camera::ScreenToLocation(Vector2 location)
{
	location += m_Position;
	return location;
}

SDL_Rect Camera::ScreenToLocation(SDL_Rect location)
{
	location.x += (int)m_Position.x;
	location.y += (int)m_Position.y;
	return location;
}

Vector2 Camera::GetPosition()
{
	return m_Position;
}

Vector2 Camera::GetViewPortSize()
{
	return m_ViewPortSize;
}

//May use for zooming and such
//void Camera::CalcViewPort(float amount)
//{
//	m_ViewPortSize.x *= amount;
//	m_ViewPortSize.y *= amount;
//}