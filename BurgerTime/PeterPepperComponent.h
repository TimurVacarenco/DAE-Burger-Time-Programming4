#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "EnumClasses.h"
namespace dae {
    class AnimationRenderComponent;
    class CollisionComponent;
    class TransformComponent;

    class PeterPepperComponent : public BaseComponent
    {
    public:
        PeterPepperComponent(GameObject* owner);
        void Update(float deltaTime) override;
        void FixedUpdate(float) {}

        void SetState(CharacterState state) { m_State = state; }
        CharacterState GetState() const { return m_State; }
        
        void InitAnimation(AnimationRenderComponent* comp);
        void Hit();
        void SetSecondPlayer(GameObject* secondPlayer) { m_SecondPlayer = secondPlayer; }
        void AddPoints(GameObject* go);
        void AddPoints(int amount);

    private:
        void HandleMovement(float deltaTime);
        void HandleAnim(float deltaTime);
        
        TransformComponent* m_Transform = nullptr;

        RenderComponent* m_Render = nullptr;

        CollisionComponent* m_Collision = nullptr;

        AnimationRenderComponent* m_Anim{};

        GameObject* m_SecondPlayer = nullptr;

        CharacterState m_State = CharacterState::idle;
        
        float m_Speed = 80.f;
        float m_ElapsedInv{};
        float m_InvTime{ 2.f };

        int m_Idle{};
        int m_RunLeft{};
        int m_RunRight{};
        int m_Climb{};
        int m_ClimbDown{};

        bool m_OnPlatform{ false };
        bool m_OnLadder{ false };
        bool m_Hit{ false };
    };
}