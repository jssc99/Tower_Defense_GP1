#pragma once

#include <stdlib.h>
#include <cmath>

#include "types.hpp"

static inline float2 operator+(float2 a, float2 b) { return { a.x + b.x, a.y + b.y }; }
static inline float2 operator+(float2 a, float b) { return { a.x + b, a.y + b }; }
static inline float2 operator-(float2 a, float2 b) { return { a.x - b.x, a.y - b.y }; }
static inline float2 operator-(float2 a, float b) { return { a.x - b, a.y - b }; }
static inline float2 operator*(float2 a, float2 b) { return { a.x * b.x, a.y * b.y }; }
static inline float2 operator*(float2 a, float b) { return { a.x * b, a.y * b }; }
static inline float2 operator/(float2 a, float2 b) { return { a.x / b.x, a.y / b.y }; }
static inline float2 operator/(float2 a, float b) { return { a.x / b, a.y / b }; }
static inline float2& operator+=(float2& a, float2 b) { a = a + b; return a; }
static inline float2& operator+=(float2& a, float b) { a = a + b; return a; }
static inline float2& operator-=(float2& a, float2 b) { a = a - b; return a; }
static inline float2& operator-=(float2& a, float b) { a = a - b; return a; }
static inline float2& operator*=(float2& a, float2 b) { a = a * b; return a; }
static inline float2& operator*=(float2& a, float b) { a = a * b; return a; }
static inline float2& operator/=(float2& a, float2 b) { a = a / b; return a; }
static inline float2& operator/=(float2& a, float b) { a = a / b; return a; }

static inline bool operator== (float2 a, float2 b) { if (a.x - b.x <= 0.0001 && a.y - b.y <= 0.0001) return true; else return false; }
static inline bool operator!= (float2 a, float2 b) { return !(a == b); }

namespace calc
{
	static const float GRAVITY = 9.80665f;
	static const float TAU = 6.28318530717958f;
	static const float PI = 3.14159265359f;

	static inline float sign(float x) { return (x < 0.f) ? -1.f : 1.f; }

	static inline float dot(float2 a, float2 b) { return a.x * b.x + a.y * b.y; }
	static inline float lengthSq(float2 v) { return dot(v, v); }
	static inline float length(float2 v) { return sqrtf(lengthSq(v)); }

	static inline float lerp(float a, float b, float t)
	{
		return (1.f - t) * a + t * b;
	}

	static inline float randomFloat(float min, float max)
	{
		float rand01 = (rand() % RAND_MAX) / (float)RAND_MAX;
		return lerp(min, max, rand01);
	}

	static inline float max(float x, float maxValue)
	{
		return (x > maxValue) ? x : maxValue;
	}

	static inline float min(float x, float minValue)
	{
		return (x < minValue) ? x : minValue;
	}

	static inline float clamp(float x, float minValue, float maxValue)
	{
		return min(max(x, minValue), maxValue);
	}
}