#pragma once

#include "Structs.h"

namespace dae
{
	class Scene;
	class Plate
	{
	public:
		Plate(dae::Scene& scene, Vector2 loc);
		~Plate() = default;
		Plate(const Plate& other) = delete;
		Plate(Plate&& other) noexcept = delete;
		Plate& operator=(const Plate& other) = delete;
		Plate& operator=(Plate&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene, Vector2 loc);
	};
}