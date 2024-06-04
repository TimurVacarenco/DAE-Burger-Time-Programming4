#include "PepperComponent.h"

#include "GameObject.h"

dae::PepperComponent::PepperComponent(GameObject* owner)
	:BaseComponent(owner)
{
}

void dae::PepperComponent::Update(float deltaTime)
{
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	switch (m_State)
	{
	case CharacterState::idle:
		break;
	case CharacterState::left:
		pos.x -= m_Speed * deltaTime;
		GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
		break;
	case CharacterState::right:
		pos.x += m_Speed * deltaTime;
		GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
		break;
	case CharacterState::up:
		pos.y -= m_Speed * deltaTime;
		GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
		break;
	case CharacterState::down:
		pos.y += m_Speed * deltaTime;
		GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
		break;
	}
}