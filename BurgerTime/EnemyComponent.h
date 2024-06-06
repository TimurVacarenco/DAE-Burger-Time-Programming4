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

	class EnemyComponent: public BaseComponent
	{
	public:
		EnemyComponent(GameObject* owner);

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void SetState(EnemyState state);
		void InitAnimation(AnimationRenderComponent* animComp, std::string textureLocation);
		void SetPeter(GameObject* peterObj);
	private:
		void HandleMovement(float deltaTime);
		void HandleCollision(float deltaTime);
		void HandleAnimation() const;

		void Initialize();

		EnemyState m_State = EnemyState::left;

		float m_Speed{ 40.f };
		float m_ClimbSpeed{ 30.f };
		float m_FallingSpeed{ 100.f };
		
		bool m_OnPlatform{ false };
		bool m_OnLadder{ false };
		bool m_Horizontal{ false };
		bool m_Switched{ false };

		Rect m_Bounds;

		GameObject* m_Peter{};
		GameObject* m_CurrentPlaform{};

		Vector2 m_Direction{};

		AnimationRenderComponent* m_Anim{};

		int m_RunLeft{};
		int m_RunRight{};
		int m_Climb{};
		int m_ClimbDown{};
		int m_Stunned{};
	};
}


