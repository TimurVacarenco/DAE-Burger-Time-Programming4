#pragma once
#include <memory>

#include "TransformComponent.h"

namespace dae
{
	class Scene;
	class PeterPepper
	{
	public:
		PeterPepper(dae::Scene& scene, Vector2 loc);
		~PeterPepper() = default;
		PeterPepper(const PeterPepper& other) = delete;
		PeterPepper(PeterPepper&& other) noexcept = delete;
		PeterPepper& operator=(const PeterPepper& other) = delete;
		PeterPepper& operator=(PeterPepper&& other) noexcept = delete;

		GameObject* GetGameObject();
	private:
		void Initialize(dae::Scene& scene, Vector2 loc);
		float m_Height{32};
		float m_Width{32};
		GameObject* m_Peter{};
	};
}