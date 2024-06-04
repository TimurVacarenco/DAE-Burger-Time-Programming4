#pragma once

#include "Structs.h"

namespace dae
{
	class Scene;
	class Wall
	{
	public:
		Wall(dae::Scene& scene, Vector2 loc);
		~Wall() = default;
		Wall(const Wall& other) = delete;
		Wall(Wall&& other) noexcept = delete;
		Wall& operator=(const Wall& other) = delete;
		Wall& operator=(Wall&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene, Vector2 loc);
	};
}