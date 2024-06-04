#pragma once
#include "Structs.h"
namespace dae
{
	class Scene;
	class Ladder
	{
	public:
		Ladder(dae::Scene& scene, Vector2 loc);
		~Ladder() = default;
		Ladder(const Ladder& other) = delete;
		Ladder(Ladder&& other) noexcept = delete;
		Ladder& operator=(const Ladder& other) = delete;
		Ladder& operator=(Ladder&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene, Vector2 loc);
	};
}