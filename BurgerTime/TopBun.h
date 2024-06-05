#pragma once

#include "Structs.h"
namespace  dae
{
	class Scene;
	class TopBun
	{
	public:
		TopBun(dae::Scene& scene, Vector2 loc);
		~TopBun() = default;
		TopBun(const TopBun& other) = delete;
		TopBun(TopBun&& other) noexcept = delete;
		TopBun& operator=(const TopBun& other) = delete;
		TopBun& operator=(TopBun&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene, Vector2 loc);
	};
}
