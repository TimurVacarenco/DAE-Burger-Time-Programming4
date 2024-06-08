#include "MenuComponent.h"

#include <iostream>
#include <thread>

#include "GameInstance.h"
#include "NextScreen.h"
#include "TextComponent.h"
#include "../3rdParty/SDL2/include/SDL_keyboard.h"

void dae::MenuComponent::SetTextComps(const std::vector<TextComponent*>& textComps)
{
	m_SinglePlayer = textComps.at(0);
	m_Coop = textComps.at(1);
	m_Versus = textComps.at(2);
	m_Name = textComps.at(3);

}

void dae::MenuComponent::NextSelection()
{
	switch (m_Selection)
	{
	case MenuSelection::singleplayer:
		m_Selection = MenuSelection::coop;
		m_SinglePlayer->SetColor(1, 1, 1, 1);
		m_Coop->SetColor(1, 0, 0, 1);
		break;
	case MenuSelection::coop:
		m_Selection = MenuSelection::versus;
		m_Coop->SetColor(1, 1, 1, 1);
		m_Versus->SetColor(1, 0, 0, 1);
		break;
	case MenuSelection::versus:
		m_Selection = MenuSelection::singleplayer;
		m_Versus->SetColor(1, 1, 1, 1);
		m_SinglePlayer->SetColor(1, 0, 0, 1);
		break;
	}
}

void dae::MenuComponent::PreviousSelection()
{
	switch (m_Selection)
	{
	case MenuSelection::singleplayer:
		m_Selection = MenuSelection::versus;
		m_SinglePlayer->SetColor(1, 1, 1, 1);
		m_Versus->SetColor(1, 0, 0, 1);
		break;
	case MenuSelection::coop:
		m_Selection = MenuSelection::singleplayer;
		m_Coop->SetColor(1, 1, 1, 1);
		m_SinglePlayer->SetColor(1, 0, 0, 1);
		break;
	case MenuSelection::versus:
		m_Selection = MenuSelection::coop;
		m_Versus->SetColor(1, 1, 1, 1);
		m_Coop->SetColor(1, 0, 0, 1);
		break;
	}
}

void dae::MenuComponent::Update(float)
{
	if (m_Started)
	{
		char ch = GetPressedKey();
		if (ch == '\n')
		{
			switch (m_Selection)
			{
			case MenuSelection::singleplayer:
				GameInstance::GetInstance().SetGameMode(GameMode::singleplayer);
				break;
			case MenuSelection::coop:
				GameInstance::GetInstance().SetGameMode(GameMode::coop);
				break;
			case MenuSelection::versus:
				GameInstance::GetInstance().SetGameMode(GameMode::versus);
				break;
			}
			GameInstance::GetInstance().SetName(m_NameStr);
			NextScreen{};
		}
		else if (ch != '\0')
		{
			if (ch != m_LastKey)
			{
				m_LastKey = ch;
				m_NameStr.push_back(ch);
				m_Name->SetText(m_NameStr);
			}
		}
		else
			m_LastKey = ch;

	}
}


void dae::MenuComponent::Start()
{

	m_Started = true;
	m_Name->SetText("ENTER NAME");
}

char dae::MenuComponent::GetPressedKey() {

	const Uint8* state = SDL_GetKeyboardState(nullptr);

	for (int scancode = SDL_SCANCODE_A; scancode <= SDL_SCANCODE_Z; ++scancode) {
		if (state[scancode]) {
			return static_cast<char>('A' + (scancode - SDL_SCANCODE_A));
		}
	}
	if (state[SDL_SCANCODE_RETURN])
		return '\n';
	return '\0';
}