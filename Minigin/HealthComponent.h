#pragma once

#include "BaseComponent.h"
#include "Subject.h"

namespace dae {
    class HealthComponent : public BaseComponent, public Subject
    {
    public:
        void Update(float) override {}
        void FixedUpdate(float) override {}
        HealthComponent(GameObject* owner) : BaseComponent(owner) {}
        int GetLives() { return m_Lives; }
        void SetLives(int lives) { m_Lives = lives; }
        void Hit(int amt = 1);
        void Kill();
    private:
        int m_Lives = 3;
    };
}
