#pragma once
#include "RenderComponent.h"
#include "Structs.h"
#include <vector>

namespace dae
{
	class Texture2D;
	class AnimationRenderComponent:public RenderComponent
	{
	public:
		AnimationRenderComponent(GameObject* owner);
		void Render() const override;
		void Update(float deltaTime) override;
	
		int AddClip(int colAmt, bool looping);
		void SetSpriteDimensions(float width, float height);
	
		void SetClip(int idx);
	private:
		std::vector<AnimationClip> m_Clips{};
		Rect m_Rect{};
	
		float m_SpriteWidth{};
		float m_SpriteHeight{};
	
		int m_ColNr{};
		int m_AnimIdx{};
		int m_FPS{ 10 };
	
		float m_ElapsedSec{};
	
	
	};
}
