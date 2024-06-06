#pragma once
#include "Structs.h"
namespace dae
{
	class Scene;
	class GameObject;
	class MrEgg
	{
	public:
		MrEgg(dae::Scene& scene, Vector2 loc, GameObject* peter);
		~MrEgg() = default;
		MrEgg(const MrEgg& other) = delete;
		MrEgg(MrEgg&& other) noexcept = delete;
		MrEgg& operator=(const MrEgg& other) = delete;
		MrEgg& operator=(MrEgg&& other) noexcept = delete;

	private:
		void Initialize(dae::Scene& scene, Vector2 loc, GameObject* peter);

		float m_Height{ 32 };
		float m_Width{ 32 };
	};
}