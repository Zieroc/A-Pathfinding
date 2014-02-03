#include "Vector2.h"

Vector2::Vector2()
{
}

Vector2::Vector2(float xVal, float yVal)
{
	x = xVal;
	y = yVal;
}

Vector2::~Vector2()
{
}

void Vector2::Clamp(Vector2 lowBounds, Vector2 highBounds)
{
	if(x < lowBounds.x)
	{
		x = lowBounds.x;
	}
	else if(x > highBounds.x)
	{
		x = highBounds.x;
	}

	if(y < lowBounds.y)
	{
		y = lowBounds.y;
	}
	else if(y > highBounds.y)
	{
		y = highBounds.y;
	}
}

Vector2 Vector2::operator+(const Vector2& other)
{
	Vector2 result;
	result.x = x + other.x;
	result.y = y + other.y;
	return result;
}

Vector2 Vector2::operator-(const Vector2& other)
{
	Vector2 result;
	result.x = x - other.x;
	result.y = y - other.y;
	return result;
}

Vector2 Vector2::operator*(const Vector2& other)
{
	Vector2 result;
	result.x = x * other.x;
	result.y = y * other.y;
	return result;
}

Vector2 Vector2::operator/(const Vector2& other)
{
	Vector2 result;
	result.x = x / other.x;
	result.y = y / other.y;
	return result;
}

void Vector2::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;
}

Vector2 Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2 Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

Vector2 Vector2::operator/=(const Vector2& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

bool Vector2::operator==(const Vector2& other)
{
	if(x == other.x && y == other.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}