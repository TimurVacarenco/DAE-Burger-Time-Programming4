#pragma once
#include <string>

struct Rect
{
	float x;
	float y;
	float width;
	float height;
};

struct Vector2
{
	float x, y;
};

struct Vector3
{
	float x, y,z;
	Vector3 operator+(const Vector3& v) const
	{
		return { x + v.x, y + v.y, z + v.z };
	}
	Vector3 operator-(const Vector3& v) const
	{
		return { x - v.x, y - v.y, z - v.z };
	}
};

struct AnimationClip
{
	int colAmt;
	bool looping = true;
};

struct Player {
	std::string name{};
	int score{};
};

struct Sound
{
	int id;
	int volume;
	bool looping;
};

struct Color
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
};