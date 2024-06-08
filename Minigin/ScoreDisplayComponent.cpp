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
	m_TextComponent->SetText("Score: ");
	m_TextComponent->SetColor(1, 1, 1, 1);
}

void dae::ScoreDisplayComponent::SetActorToDisplay(GameObject* obj)
{
	m_PointsActor = obj;
	int scoreAmt = obj->GetComponent<ScoreComponent>()->GetPoints();
	std::string score = "Score: " + std::to_string(scoreAmt);
	m_TextComponent->SetText(score);
}

void dae::ScoreDisplayComponent::OnNotify(const GameObject* obj, Event event)
{
	switch (event)
	{
	case Event::ADDED_SCORE:
		if (obj == m_PointsActor)
		{
			int scoreAmt = obj->GetComponent<ScoreComponent>()->GetPoints();
			std::string score = "Score: " + std::to_string(scoreAmt);
			m_TextComponent->SetText(score);
		}
		break;
	}
}
