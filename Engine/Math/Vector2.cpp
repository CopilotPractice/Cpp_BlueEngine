#include "Vector2.h"
#include <Windows.h>
#include <cmath> // atan atan2 등등
#include <cassert>				

namespace Blue
{
	//기본 값
	const Vector2 Vector2::Zero = Vector2(0.0f,0.0f); // static은 객체 초기화 하는 시점과 다름.
	const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
	const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
	const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);

	std::wstring Vector2::ToString()
	{
		wchar_t buffer[256];
		swprintf_s(buffer, TEXT("(%f,%f)"), x, y);
		return buffer;
	}
	float Vector2::Length()
	{
		return sqrtf(x * x + y * y);
	}
	Vector2 operator+(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x + right.x, left.y + right.y);
	}
	Vector2 operator-(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x - right.x, left.y - right.y);
	}
	Vector2 operator*(const Vector2& vector, float scale)
	{
		return Vector2(vector.x * scale, vector.y * scale);
	}
	Vector2 operator*(float scale, const Vector2& vector)
	{
		return Vector2(vector.x * scale, vector.y * scale);
	}
	Vector2 operator/(const Vector2& vector, float scale)
	{
		assert(scale != 0.0f);
		return Vector2(vector.x / scale, vector.y /scale);
	}
	Vector2 Lerp(const Vector2& from, const Vector2& to, float t)
	{
		if (t < 0.0f)
		{
			t = 0.0f;
		}
		if (t > 1.0f)
		{
			t = 1.0f;
		}
		return (1.0f - t) * from + t * to;                    // ~~~중요
	}
	float Dot(const Vector2& left, const Vector2& right)
	{
		return (left.x * right.x) + (left.y * right.y);
	}
	Vector2 Vector2::Normalized()
	{
		float length = Length();
		return Vector2(x/length, y/length);
	}
	bool Vector2::Equals(const Vector2& other)
	{

		return x == other.x && y==other.y; // 부동소수점은 오차가 존재할 확률이 매우 높기 때문에
		                                   //
	}
	Vector2& Vector2::operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;

		return *this;

	}
	Vector2& Vector2::operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}
	Vector2& Vector2::operator*=(float scale)
	{
		x *= scale;
		y *= scale;

		return *this;
	}
	Vector2& Vector2::operator/=(float scale)
	{
		//divide by zero 조심
		assert(scale != 0.0f); // 0이면 error

		x /= scale;
		y /= scale;

		return *this;
	}
	bool Vector2::operator==(const Vector2& other)
	{
		return x == other.x && y== other.y;
	}
	bool Vector2::operator!=(const Vector2& other)
	{
		return x != other.x || y != other.y;
	}
	Vector2 Vector2::operator-() const
	{
		return Vector2(-x, -y);
	}
}