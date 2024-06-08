#pragma once
#include <string>
#include <vector>
#include "EnumClasses.h"
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;

	class MenuComponent : public BaseComponent
	{
	public:
		MenuComponent(GameObject* owner) :BaseComponent(owner) {}

		void Update(float) override;
		void FixedUpdate(float) override {}

		void SetTextComps(const std::vector<TextComponent*>& textComps);

		void NextSelection();
		void PreviousSelection();
		void Start();

	private:
		char GetPressedKey();
		TextComponent* m_SinglePlayer = nullptr;
		TextComponent* m_Coop = nullptr;
		TextComponent* m_Versus = nullptr;
		TextComponent* m_Name = nullptr;

		std::string m_NameStr;
		MenuSelection m_Selection = MenuSelection::singleplayer;
		bool m_Started = false;

		char m_LastKey = ';';
	};
}


