#pragma once
#include <memory>

#include "TransformComponent.h"

namespace dae
{
	class Scene;
	class PeterPepper
	{
	public:
		PeterPepper(dae::Scene& scene);
		~PeterPepper() = default;
		PeterPepper(const PeterPepper& other) = delete;
		PeterPepper(PeterPepper&& other) noexcept = delete;
		PeterPepper& operator=(const PeterPepper& other) = delete;
		PeterPepper& operator=(PeterPepper&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene);
		std::shared_ptr<dae::TransformComponent> m_Transform{};
	};
}