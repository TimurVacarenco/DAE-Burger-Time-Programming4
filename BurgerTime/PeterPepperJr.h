#pragma once
#include "Structs.h"
namespace dae
{
	class Scene;
	class GameObject;
	class PeterPepperJr
	{
	public:
		PeterPepperJr(dae::Scene& scene, Vector2 loc, bool keyboardControls = true);
		~PeterPepperJr() = default;
		PeterPepperJr(const PeterPepperJr& other) = delete;
		PeterPepperJr(PeterPepperJr&& other) noexcept = delete;
		PeterPepperJr& operator=(const PeterPepperJr& other) = delete;
		PeterPepperJr& operator=(PeterPepperJr&& other) noexcept = delete;

		GameObject* GetGameObject();

	private:
		void Initialize(dae::Scene& scene, Vector2 loc, bool keyboardControls);

		float m_Height{ 32 };
		float m_Width{ 32 };
		GameObject* m_PeterJr{};

	};
}
