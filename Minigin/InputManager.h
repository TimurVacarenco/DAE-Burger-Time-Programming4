#pragma once
#include "Input.h"
#include "Singleton.h"


namespace dae
{
	class InputManager : public Singleton<InputManager>
	{
		Input m_input{};
	public:
		InputManager();
		~InputManager() = default;

		bool HandleInput();

		bool IsPressed(ControllerButton button, int controllerIdx);

		void AddCommand(Input::ControllerKey controllerKey, std::shared_ptr<BaseCommand> command);
		void AddCommand(Input::KeyCommand keyCommand, std::shared_ptr<BaseCommand> command);
		void RemoveCommand(Input::ControllerKey controllerKey);
		void RemoveCommands();

		void AddController(int idx) { m_input.AddController(idx); }

	private:
		float m_ControllerCheckInterval = 1.f;
		float m_ElapsedControllerCheck = 1.f;
	};
}
