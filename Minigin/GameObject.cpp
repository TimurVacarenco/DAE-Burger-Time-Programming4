#include "GameObject.h"

#include "BaseComponent.h"
#include "RenderComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (std::shared_ptr<BaseComponent> comp : m_Components)
	{
		comp->FixedUpdate(deltaTime);
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (std::shared_ptr<BaseComponent>& comp : m_Components)
	{
		comp->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (auto render : GetComponents<RenderComponent>())
	{
		render->Render();
	}
}

dae::GameObject* dae::GameObject::GetParent()
{
	return m_Parent;
}

void dae::GameObject::SetParent(GameObject* parent, bool worldPosStays)
{
	if (m_Parent)
	{
		m_Parent->RemoveChild(this);
	}

	m_Parent = parent;

	if (!m_Parent)
	{
		return;
	}
	m_Parent->AddChild(this);

	if (!worldPosStays)
	{
		GetTransform()->SetLocalPosition(0, 0, 0);
	}
	else
	{
		GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() - parent->GetTransform()->GetWorldPosition());

	}
}

void dae::GameObject::AddChild(GameObject* child)
{

	auto previousParent = child->GetParent();

	if (previousParent != this)
	{
		previousParent->RemoveChild(child);
	}

	m_Children.push_back(child);

}

void dae::GameObject::RemoveChild(GameObject* child)
{
	m_Children.erase(std::find(m_Children.begin(), m_Children.end(), child));
	child->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + child->GetTransform()->GetLocalPosition());
	child->m_Parent = nullptr;
}

void dae::GameObject::SetTag(Tag tag)
{
	m_Tag = tag;
}

const Tag& dae::GameObject::GetTag() const
{
	return m_Tag;
}

std::vector<dae::GameObject*> dae::GameObject::GetChildren() const
{
	return m_Children;
}

dae::TransformComponent* dae::GameObject::GetTransform()
{
	return m_Transform;
}
