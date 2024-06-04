#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "EnumClasses.h"

namespace dae {
    class PepperComponent : public BaseComponent
    {
    public:
        PepperComponent(GameObject* owner);
        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}
        void SetState(CharacterState state) { m_State = state; }
    private:
        CharacterState m_State = CharacterState::idle;
        float m_Speed = 30.f;
    };
}