#pragma once
#include <map>
#include <memory>
#include <SDL_scancode.h>
#include <vector>
#include "PlayerController.h"
#include "BaseCommand.h"
#include "EnumClasses.h"

class Input final
{
public:
	Input() = default;
	~Input() = default;

	void AddController(int index);
	void CheckControllers();

	using ControllerKey = std::tuple<unsigned, ControllerButton, KeyState>;
	using ControllerCommandsMap = std::map<ControllerKey, std::shared_ptr<dae::BaseCommand>>;
	using KeyCommand = std::pair<SDL_Scancode, KeyState>;
	using KeyboardCommandsMap = std::map<KeyCommand, std::shared_ptr<dae::BaseCommand>>;
	KeyboardCommandsMap m_KeyCommands{};
	ControllerCommandsMap m_ConsoleCommands{};
	std::vector<std::unique_ptr<dae::PlayerController>> m_Controllers{};
};

