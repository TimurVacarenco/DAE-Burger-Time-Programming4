#pragma once
#include "Structs.h"
namespace dae
{
	class ScoreComponent;
	class Scene;
	class GameObject;
	class PlayerHotDog
	{
	public:
		PlayerHotDog(dae::Scene& scene, Vector2 loc, bool keyboardControls = true);
		~PlayerHotDog() = default;
		PlayerHotDog(const PlayerHotDog& other) = delete;
		PlayerHotDog(PlayerHotDog&& other) noexcept = delete;
		PlayerHotDog& operator=(const PlayerHotDog& other) = delete;
		PlayerHotDog& operator=(PlayerHotDog&& other) noexcept = delete;

		GameObject* GetGameObject();

	private:
		void Initialize(dae::Scene& scene, Vector2 loc, bool keyboardControls);

		float m_Height{ 32 };
		float m_Width{ 32 };

		GameObject* m_PlayerHotDog{};

	};
}
