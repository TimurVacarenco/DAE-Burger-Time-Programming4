#pragma once
#include <vector>
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "EnumClasses.h"

namespace dae{
	class CollisionComponent;

	class IngredientComponent: public BaseComponent
	{
	public:
		IngredientComponent(GameObject* Owner);
		
		void Update(float deltaTime) override;
		void FixedUpdate(float deltatime) override;
		void SetCollisions(std::vector<CollisionComponent*>& collisions);
		void SetSprites(std::vector<RenderComponent*>& sprites);
		void SetState(IngredientState state);
	private:
		void HandleMovement(float deltaTime);
		void HandleCollision(float deltaTime);
		
		IngredientState m_State = IngredientState::idle;
		std::vector<CollisionComponent*> m_Collisions{};
		std::vector<RenderComponent*> m_Sprites{};
		bool m_DropStates[4]{ false,false,false,false };
		float m_FallSpeed{ 200.f };
		GameObject* m_CollidedIngredient{ nullptr },
			* m_Platform{ nullptr };
	};

}