#pragma once

#include "Structs.h"

namespace dae
{
	class Scene;
	class Patty
	{
	public:
		Patty(dae::Scene& scene, Vector2 loc);
		~Patty() = default;
		Patty(const Patty& other) = delete;
		Patty(Patty&& other) noexcept = delete;
		Patty& operator=(const Patty& other) = delete;
		Patty& operator=(Patty&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene, Vector2 loc);
	};
}