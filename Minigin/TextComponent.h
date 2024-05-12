#pragma once
#include <memory>
#include <string>
#include "Structs.h"
#include "BaseComponent.h"

namespace dae
{

	class Font;
	class Texture2D;
	class RenderComponent;

	class TextComponent : public BaseComponent
	{
	public:
		void Update(float deltaTime) override;
		void FixedUpdate(float) override {};

		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font>& font);
		void SetColor(float r, float g, float b, float a = 1);
		void SetOffset(float x, float y);
		TextComponent(GameObject* owner);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		RenderComponent* m_RenderComponent{};
		Color m_Color{ 255,255,255,255 };
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;

	};
}


