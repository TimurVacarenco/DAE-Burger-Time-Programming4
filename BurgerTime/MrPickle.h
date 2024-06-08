#pragma once
#include "Structs.h"
namespace dae
{
	class Scene;
	class GameObject;
	class MrPickle
	{
	public:
		MrPickle(dae::Scene& scene, Vector2 loc, GameObject* peter);
		~MrPickle() = default;
		MrPickle(const MrPickle& other) = delete;
		MrPickle(MrPickle&& other) noexcept = delete;
		MrPickle& operator=(const MrPickle& other) = delete;
		MrPickle& operator=(MrPickle&& other) noexcept = delete;

	private:
		void Initialize(dae::Scene& scene, Vector2 loc, GameObject* peter);

		float m_Height{ 32 };
		float m_Width{ 32 };
	};
}
