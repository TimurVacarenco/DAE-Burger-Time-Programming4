#include "ScoreDisplayComponent.h"

#include "EnumClasses.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "ScoreComponent.h"
#include "TextComponent.h"


dae::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* owner) : BaseComponent(owner)
{
	auto font = ResourceManager::GetInstance().LoadFont("Burgertime.otf", 20);
	m_TextComponent = owner->AddComponent<TextComponent>();
	m_TextComponent->SetFont(font);
	m_TextComponent->SetText("Points: ");
	m_TextComponent->SetColor(1, 1, 1, 1);
}

void dae::ScoreDisplayComponent::SetActorToDisplay(GameObject* obj)
{
	m_PointsActor = obj;
	int pointsAmt = obj->GetComponent<ScoreComponent>()->GetPoints();
	std::string points = "Points: " + std::to_string(pointsAmt);
	m_TextComponent->SetText(points);
}

void dae::ScoreDisplayComponent::OnNotify(const GameObject* obj, Event event)
{
	switch (event)
	{
	case Event::ADDED_POINTS:
		if (obj == m_PointsActor)
		{
			int pointsAmt = obj->GetComponent<ScoreComponent>()->GetPoints();
			std::string points = "Points: " + std::to_string(pointsAmt);
			m_TextComponent->SetText(points);
		}
		break;
	}
}
