#pragma once
#include "Structs.h"

namespace dae
{
	class Scene;
	class Tomato
	{
	public:
		Tomato(dae::Scene& scene, Vector2 loc);
		~Tomato() = default;
		Tomato(const Tomato& other) = delete;
		Tomato(Tomato&& other) noexcept = delete;
		Tomato& operator=(const Tomato& other) = delete;
		Tomato& operator=(Tomato&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene, Vector2 loc);
	};
}