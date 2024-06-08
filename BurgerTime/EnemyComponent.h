#pragma once

#include <vector>

#include "BaseComponent.h"
#include "RenderComponent.h"
#include "Structs.h"
#include "EnumClasses.h"
#include "TransformComponent.h"

namespace dae
{
	class AnimationRenderComponent;
	class CollisionComponent;

	class EnemyComponent : public BaseComponent
	{
	public:
		EnemyComponent(GameObject* owner);

		void Update(float deltaTime) override;
		void FixedUpdate(float) override {}

		void SetState(EnemyState state);
		void SetPeter(GameObject* peterObj);
		EnemyState GetState() const { return m_State; }

		void InitAnimation(AnimationRenderComponent* animComp, std::string textureLocation);

		void Kill();
		void Stun();
		void CalculateDirection();
	private:
		void HandleMovement(float deltaTime);
		void HandleAnimation() const;
		void HandleStun(float deltaTime);
		void Initialize();

		EnemyState m_State = EnemyState::left;

		float m_Speed{ 30.f };
		float m_ClimbSpeed{ 20.f };
		float m_StunTime{3.f};
		float m_StunElapsed{};

		bool m_OnPlatform{ false };
		bool m_OnLadder{ false };
		bool m_DirectionChanged{ false };

		GameObject* m_Peter{};

		Vector2 m_Direction{};
		Vector2 m_MovementDirection{};
		
		CollisionComponent* m_Collision = nullptr;

		AnimationRenderComponent* m_Anim{};

		TransformComponent* m_Transform = nullptr;

		int m_RunLeft{};
		int m_RunRight{};
		int m_Climb{};
		int m_ClimbDown{};
		int m_Stunned{};
		int m_Hit{};
		int m_Fall{};
	};
}


