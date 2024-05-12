#include "HealthDisplayComponent.h"

#include "EnumClasses.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::HealthDisplayComponent::HealthDisplayComponent(GameObject* owner) : BaseComponent(owner)
{
	auto font = ResourceManager::GetInstance().LoadFont("Burgertime.otf", 20);
	m_TextComponent = owner->AddComponent<TextComponent>();
	m_TextComponent->SetFont(font);
	m_TextComponent->SetText("Lives: ");
	m_TextComponent->SetColor(1, 1, 1, 1);
}

void dae::HealthDisplayComponent::SetActorToDisplay(GameObject* obj)
{
	m_HealthActor = obj;
	int livesAmt = obj->GetComponent<HealthComponent>()->GetLives();
	std::string lives = "Lives: " + std::to_string(livesAmt);
	m_TextComponent->SetText(lives);
}


void dae::HealthDisplayComponent::OnNotify(const GameObject* obj, Event event)
{
	switch (event)
	{
	case Event::ON_HIT:
		if (obj == m_HealthActor)
		{
			int livesAmt = obj->GetComponent<HealthComponent>()->GetLives();
			std::string lives = "Lives: " + std::to_string(livesAmt);
			m_TextComponent->SetText(lives);
		}
		break;
	}
}
