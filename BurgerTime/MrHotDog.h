#pragma once
#include "Structs.h"
namespace dae
{
	class Scene;
	class GameObject;
	class MrHotDog
	{
	public:
		MrHotDog(dae::Scene& scene, Vector2 loc, GameObject* peter);
		~MrHotDog() = default;
		MrHotDog(const MrHotDog& other) = delete;
		MrHotDog(MrHotDog&& other) noexcept = delete;
		MrHotDog& operator=(const MrHotDog& other) = delete;
		MrHotDog& operator=(MrHotDog&& other) noexcept = delete;

	private:
		void Initialize(dae::Scene& scene, Vector2 loc, GameObject* peter);

		float m_Height{ 32 };
		float m_Width{ 32 };
	};
}
