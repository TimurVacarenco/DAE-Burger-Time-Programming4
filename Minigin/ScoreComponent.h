#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
    class ScoreComponent : public BaseComponent, public Subject
    {
    public:
        ScoreComponent(GameObject* owner) : BaseComponent(owner) {}
        void Update(float) override {}
        void FixedUpdate(float) override {}
        void AddPoints(int pointsAmt) { m_Points += pointsAmt; Notify(GetOwner(), Event::ADDED_POINTS); }
        int GetPoints() { return m_Points; }
    private:
        int m_Points{};
    };
}
