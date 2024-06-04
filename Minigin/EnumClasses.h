#pragma once
#pragma region EVENT
enum class Event
{
	ON_HIT,
	ON_DEATH,
	ADDED_POINTS,
	ON_PEPPER
};
#pragma endregion
#pragma region TAGS
enum class Tag
{
	platform,
	ladder,
	peter,
	hotdog,
	pickle,
	egg,
	bun,
	plate,
	cheese,
	bottombun,
	lettuce,
	patty,
	tomato,
	peterjr,
	playerhotdog,
	wall
};
#pragma endregion
#pragma region STATE
enum class EnemyState
{
	left,
	right,
	up,
	down,
	stunned,
	falling,
	dead
};
enum class IngridientState
{
	idle,
	falling,
	plated
};

enum class KeyState
{
	OnPressed,
	OnReleased,
	Held
};

enum class CharacterState
{
	idle,
	left,
	right,
	up,
	down
};

enum class PlayerHotDogState
{
	idle,
	left,
	right,
	up,
	down,
	stunned,
	falling
};
#pragma endregion
#pragma region GAMEMODE
enum class GameMode
{
	singleplayer,
	coop,
	versus
};

enum class MenuSelection
{
	singleplayer,
	coop,
	versus
};
#pragma endregion
#pragma region CONTROLLER
enum class ControllerButton
{
	DpadUp = 0x0001,
	DpadDown = 0x0002,
	DpadLeft = 0x0004,
	DpadRight = 0x0008,
	Start = 0x0010,
	Back = 0x0020,
	LeftThumb = 0x0040,
	RightThumb = 0x0080,
	LeftShoulder = 0x0100,
	RightShoulder = 0x0200,
	ButtonA = 0x1000,
	ButtonB = 0x2000,
	ButtonX = 0x4000,
	ButtonY = 0x8000
};
#pragma endregion