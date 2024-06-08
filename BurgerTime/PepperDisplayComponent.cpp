#include "PepperDisplayComponent.h"

#include "EnumClasses.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "PepperComponent.h"
#include "TextComponent.h"

dae::PepperDisplayComponent::PepperDisplayComponent(GameObject* owner) : BaseComponent(owner)
{
	auto font = ResourceManager::GetInstance().LoadFont("Burgertime.otf", 10);
	m_TextComponent = owner->AddComponent<TextComponent>();
	m_TextComponent->SetFont(font);
	m_TextComponent->SetText("Pepper: ");
	m_TextComponent->SetColor(1, 1, 1, 1);
}

void dae::PepperDisplayComponent::SetActorToDisplay(GameObject* obj)
{
	m_HealthActor = obj;
	int livesAmt = obj->GetComponent<PepperComponent>()->GetAmt();
	std::string lives = "Pepper: " + std::to_string(livesAmt);
	m_TextComponent->SetText(lives);
}


void dae::PepperDisplayComponent::OnNotify(const GameObject* obj, Event event)
{
	switch (event)
	{
	case Event::ON_PEPPER:
		if (obj == m_HealthActor)
		{
			int livesAmt = obj->GetComponent<PepperComponent>()->GetAmt();
			std::string lives = "Pepper: " + std::to_string(livesAmt);
			m_TextComponent->SetText(lives);
		}
		break;
	}
}
