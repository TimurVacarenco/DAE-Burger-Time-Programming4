#include "Level.h"
#include "LevelLoader.h"

dae::Level::Level(Scene& scene)
{
	Initialize(scene);
}


void dae::Level::Initialize(Scene&)
{
	LevelLoader loader{};
	loader.LoadLevel("../Data/Levels/level1.json");
}