#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
namespace dae
{
	class Texture2D;
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(GameObject* owner);

		void Update(float) override {};
		void FixedUpdate(float) override {};

		virtual void Render() const;
		void SetTexture(const std::shared_ptr<Texture2D> texture);
		void SetTexture(const std::string& filename);
		void SetDimensions(float width, float height);

		void SetEnabled(bool enabled) { m_Enabled = enabled; }
		void SetOffsetY(float y) { m_OffsetY = y; }
		void SetOffsetX(float x) { m_OffsetX = x; }
	protected:
		std::shared_ptr<Texture2D> m_Texture;
		float m_Width{};
		float m_Height{};
		float m_OffsetY{};
		float m_OffsetX{};
		bool m_UseDimensions{ false };
		bool m_Enabled{ true };
	};
}


