#pragma once
#include "Structs.h"

namespace dae
{
	class Scene;
	class BottomBun
	{
	public:
		BottomBun(dae::Scene& scene, Vector2 loc);
		~BottomBun() = default;
		BottomBun(const BottomBun& other) = delete;
		BottomBun(BottomBun&& other)noexcept = delete;
		BottomBun& operator=(const BottomBun& other) = delete;
		BottomBun& operator=(BottomBun&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene, Vector2 loc);
	};
};

