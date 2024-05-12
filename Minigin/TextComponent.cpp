#include "TextComponent.h"

#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <stdexcept>

#include "Renderer.h"
#include "Font.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(GameObject* owner)
	: m_NeedsUpdate(true), m_Text("NULL"), m_Font(nullptr), m_TextTexture(nullptr)
	, BaseComponent{ owner }
{
	m_RenderComponent = GetOwner()->AddComponent<RenderComponent>();

}
void dae::TextComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { m_Color.red,m_Color.green,m_Color.blue,m_Color.alpha };
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_RenderComponent->SetTexture(std::make_shared<Texture2D>(texture));
		m_NeedsUpdate = false;
	}

}


void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetFont(const std::shared_ptr<Font>& font)
{
	m_Font = font;
}

void dae::TextComponent::SetColor(float r, float g, float b, float a)
{
	m_Color.red = uint8_t(r * 255);
	m_Color.green = uint8_t(g * 255);
	m_Color.blue = uint8_t(b * 255);
	m_Color.alpha = uint8_t(a * 255);

	m_NeedsUpdate = true;
}

void dae::TextComponent::SetOffset(float x, float y)
{
	m_RenderComponent->SetOffsetX(x);
	m_RenderComponent->SetOffsetY(y);
}
