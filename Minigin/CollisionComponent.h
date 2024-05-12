#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace dae {
	class CollisionComponent : public BaseComponent
	{
	public:
		CollisionComponent(GameObject* owner) : BaseComponent(owner) {}

		void Update(float) override {}
		void FixedUpdate(float) override {}

        void SetSize(float width, float height);
        void SetOffset(float x, float y) { m_OffsetX = x; m_OffsetY = y; }

        bool IsOverlapping(GameObject* other);
        bool IsOverlapping(Rect other);

        bool IsUnder(GameObject* other);
        bool IsUnder(Rect other);

        bool IsToSide(GameObject* other);
        bool IsToSide(Rect other);
    private:
        float m_Width{};
        float m_Height{};
        float m_OffsetX{};
        float m_OffsetY{};
	};
}

