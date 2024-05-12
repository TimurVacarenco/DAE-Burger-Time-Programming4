#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"

dae::RenderComponent::RenderComponent(GameObject* owner)
	:BaseComponent{ owner }
{}
void dae::RenderComponent::Render() const
{
	if (m_Enabled)
	{
		if (m_Texture != nullptr)
		{
			auto pos = GetOwner()->GetTransform()->GetWorldPosition();

			if (m_UseDimensions)
			{
				Renderer::GetInstance().RenderTexture(*m_Texture, pos.x + m_OffsetX, pos.y + m_OffsetY, m_Width, m_Height);
			}
			else
			{
				Renderer::GetInstance().RenderTexture(*m_Texture, pos.x + m_OffsetX, pos.y + m_OffsetY);
			}
		}
	}
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetDimensions(float width, float height)
{
	m_UseDimensions = true;
	m_Width = width;
	m_Height = height;
}
