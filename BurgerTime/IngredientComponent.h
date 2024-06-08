#pragma once
#include <vector>

#include "BaseComponent.h"
#include "RenderComponent.h"
#include "EnumClasses.h"
namespace dae {
    class CollisionComponent;

    class IngredientComponent : public BaseComponent
    {
    public:

        IngredientComponent(GameObject* owner);

        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}

        void SetCollisions(std::vector<CollisionComponent*>& cols);
        void SetSprites(std::vector<RenderComponent*>& sprites);

        void SetState(IngredientState state);
        bool Plated()const { return m_State == IngredientState::plated; }
    private:
        void Initialize();
        void HandleMovement(float deltaTime);
        void HandleCollision(float deltaTime);

        IngredientState m_State = IngredientState::idle;

        std::vector<CollisionComponent*> m_Collisions{};
        std::vector<RenderComponent*> m_Sprites{};

        bool m_DropStates[4]{ false,false,false,false };
        bool m_Next = false;

        float m_FallSpeed{ 150.f };

        GameObject* m_CollidedIngredient{ nullptr };
        GameObject* m_Platform{ nullptr };
        GameObject* m_PlayerHotDog = nullptr;
        GameObject* m_Peter = nullptr;

        std::vector<GameObject*> m_Enemies{};
        
        int m_LevelsToFall = 0;
        int m_Walk{};
        int m_Bounce{};


             
    };
}
