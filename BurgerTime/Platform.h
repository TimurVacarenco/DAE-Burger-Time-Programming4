#pragma once
#include "Structs.h"

namespace dae
{
	class Scene;
	class Platform
	{
	public:
		Platform(dae::Scene& scene, Vector2 loc);
		~Platform() = default;
		Platform(const Platform& other) = delete;
		Platform(Platform&& other) noexcept = delete;
		Platform& operator=(const Platform& other) = delete;
		Platform& operator=(Platform&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene, Vector2 loc);
	};
}