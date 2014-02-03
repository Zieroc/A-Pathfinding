#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
	Vector2();
	Vector2(float xVal, float yVal);
	~Vector2();
	void Clamp(Vector2 lowBounds, Vector2 highBounds);
	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator*(const Vector2& other);
	Vector2 operator/(const Vector2& other);
    void operator=(const Vector2& other);
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	Vector2 operator*=(const Vector2& other);
	Vector2 operator/=(const Vector2& other);
	bool operator==(const Vector2& other);
	float x;
	float y;
};

#endif