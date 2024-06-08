#pragma once
#include <string>

class LevelLoader
{
public:
	LevelLoader() = delete;
	~LevelLoader() = delete;
	LevelLoader(const LevelLoader& other) = delete;
	LevelLoader(LevelLoader&& other) noexcept = delete;
	LevelLoader& operator=(const LevelLoader& other) = delete;
	LevelLoader& operator=(LevelLoader&& other) noexcept = delete;

	static void LoadLevel(const std::string& fileLoc);
	static void ReloadLevel(const std::string& fileLoc);
};

