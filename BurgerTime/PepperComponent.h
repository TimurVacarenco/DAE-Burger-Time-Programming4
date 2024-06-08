#pragma once
#include "RenderComponent.h"
#include "Subject.h"

namespace dae {
	class GameObject;

	class PepperComponent : public BaseComponent, public Subject
	{
	public:
		PepperComponent(GameObject* owner);
		void Update(float)override;
		void FixedUpdate(float) override {}
		void Activate();
		int GetAmt()const { return m_Amt; }
	private:
		void Initialize();

		GameObject* m_Peter{};

		dae::RenderComponent* m_RenderComp{};
		
		bool m_Active{ false };

		float m_TimeToShow{ .5f };
		float m_ElapsedTime{};

		int m_Amt{ 5 };
		int m_Sound{};
	};
}
