#pragma once
#include <string>
#include "../Core/Type.h"

namespace Blue
{
	// 2차원 벡터 클래스
	class Vector2
	{
	public:
		float x;  //double로 하면 더 정확하겠지만, 공간을 많이 차지해서 
		float y;  // 조금 부정확하지만 부동소수점 활용

		Vector2()
			: x(0.0f), y(0.0f)
		{

		}
		Vector2(float value)
			: x(value), y(value)
		{

		}
		Vector2(float x, float y)
			: x(x), y(y)
		{
		}
		//메모리 크기(Stride)
		static uint32 Stride() { return sizeof(Vector2); }

		//연산자 오버로딩
		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);
		Vector2& operator*=(float scale);
		Vector2& operator/=(float scale);

		bool operator==(const Vector2& other);
		bool operator!=(const Vector2& other);

		Vector2 operator-() const;

		friend Vector2 operator+(const Vector2& left, const Vector2& right);
		friend Vector2 operator-(const Vector2& left, const Vector2& right);
		friend Vector2 operator*(const Vector2& vector, float scale);
		friend Vector2 operator*(float scale, const Vector2& vector);
		friend Vector2 operator/(const Vector2& vector, float scale);


		//std::wstring ToString();
		//선형 보간(Lerp - Linear Interpolation)
		//(1-t) * from + t * to;
		friend Vector2 Lerp(const Vector2& from, const Vector2& to, float t);

		//기본 값
		static const Vector2 Zero; // static은 객체 초기화 하는 시점과 다름.
		static const Vector2 One; 
		static const Vector2 Right; 
		static const Vector2 Up; 

		// (x, y) 문자열 생성 함수
		std::wstring ToString();

		// 길이 구하기
		float Length();
		friend float Dot(const Vector2& left, const Vector2& right); // 두 벡터의 사이각 구하기
		Vector2 Normalized();
		bool Equals(const Vector2& other);


	};
}