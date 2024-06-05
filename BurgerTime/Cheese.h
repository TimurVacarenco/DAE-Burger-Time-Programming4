#pragma once
#include "Structs.h"

namespace dae
{
	class Scene;
	class Cheese
	{
	public:
		Cheese(dae::Scene& scene, Vector2 loc);
		~Cheese() = default;
		Cheese(const Cheese& other) = delete;
		Cheese(Cheese&& other) noexcept = delete;
		Cheese& operator=(const Cheese& other) = delete;
		Cheese& operator=(Cheese&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene, Vector2 loc);
	};
}