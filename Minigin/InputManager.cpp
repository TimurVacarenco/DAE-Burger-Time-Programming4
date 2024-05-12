#include "InputManager.h"
#include "BaseCommand.h"
#include <SDL_events.h>

#include "ServiceLocator.h"
#include "../BurgerTime/GameInstance.h"

dae::InputManager::InputManager()
{

}

bool dae::InputManager::HandleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			for (const auto& command : m_input.m_KeyCommands)
			{
				if (command.first.second == KeyState::OnPressed)
				{
					if (e.key.keysym.scancode == command.first.first)
						command.second.get()->Execute();
				}
			}
		}
		if (e.type == SDL_KEYUP)
		{
			for (const auto& command : m_input.m_KeyCommands)
			{
				if (command.first.second == KeyState::OnReleased)
				{
					if (e.key.keysym.scancode == command.first.first)
						command.second.get()->Execute();
				}
			}

			if (e.key.keysym.scancode == SDL_SCANCODE_M)
			{
				ServiceLocator::GetSoundSystem().Mute();
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_F1)
			{
				GameInstance::GetInstance().SkipLevel();
			}
		}
	}

	for (auto& controller : m_input.m_Controllers)
	{
		controller->Update();
	}
	auto it = m_input.m_ConsoleCommands.begin();
	while (it != m_input.m_ConsoleCommands.end())
	{

		if (std::get<2>(it->first) == KeyState::OnPressed)
		{
			if (m_input.m_Controllers.at(std::get<0>(it->first))->IsDown(std::get<1>(it->first)))
			{
				it->second->Execute();
			}
		}
		if (std::get<2>(it->first) == KeyState::OnReleased)
		{
			if (m_input.m_Controllers.at(std::get<0>(it->first))->IsUp(std::get<1>(it->first)))
			{
				it->second->Execute();
			}
		}
		if (std::get<2>(it->first) == KeyState::Held)
		{
			if (m_input.m_Controllers.at(std::get<0>(it->first))->IsPressed(std::get<1>(it->first)))
			{
				it->second->Execute();
			}
		}
		++it;
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button, int controllerIdx)
{
	return m_input.m_Controllers.at(controllerIdx)->IsPressed(button);
}


void dae::InputManager::AddCommand(Input::ControllerKey controllerKey, std::shared_ptr<BaseCommand> command)
{
	m_input.m_ConsoleCommands.insert({ controllerKey, command });
}

void dae::InputManager::AddCommand(Input::KeyCommand keyCommand, std::shared_ptr<BaseCommand> command)
{
	m_input.m_KeyCommands.insert({ keyCommand, command });
}

void dae::InputManager::RemoveCommand(Input::ControllerKey controllerKey)
{
	m_input.m_ConsoleCommands.erase(controllerKey);
}

void dae::InputManager::RemoveCommands()
{
	m_input.m_ConsoleCommands.clear();
	m_input.m_KeyCommands.clear();
}