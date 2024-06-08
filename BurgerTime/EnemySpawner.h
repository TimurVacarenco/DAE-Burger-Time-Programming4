#pragma once
#include "Structs.h"

namespace dae
{
	class Scene;
}

class EnemySpawner
{
public:
	EnemySpawner(dae::Scene& scene, Vector2 loc);
	~EnemySpawner() = default;
	EnemySpawner(const EnemySpawner& other) = delete;
	EnemySpawner(EnemySpawner&& other) noexcept = delete;
	EnemySpawner& operator=(const EnemySpawner& other) = delete;
	EnemySpawner& operator=(EnemySpawner&& other) noexcept = delete;
private:
	void Initialize(dae::Scene& scene, Vector2 loc);
};
