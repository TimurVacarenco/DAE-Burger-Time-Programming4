#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#include "PlayerController.h"


using namespace dae;

//PIMPL Pattern
class PlayerController::PlayerControllerImpl
{
	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};

	WORD buttonsPressedThisFrame;
	WORD buttonsReleasedThisFrame;

	int _controllerIndex;
public:
	PlayerControllerImpl(int controllerIndex)
	{
		ZeroMemory(&previousState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		_controllerIndex = controllerIndex;
	}

	void Update()
	{
		CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(_controllerIndex, &currentState);

		auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
		buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
		buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
	}


	bool IsDownThisFrame(unsigned int button) const { return buttonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return buttonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return currentState.Gamepad.wButtons & button; }


	int GetIndex() { return _controllerIndex; }
};

PlayerController::PlayerController(int controllerIndex)
{
	pImpl = new PlayerControllerImpl(controllerIndex);
}


PlayerController::~PlayerController()
{
	delete pImpl;
}

void PlayerController::Update()
{
	pImpl->Update();
}


bool PlayerController::IsDown(ControllerButton button) const
{
	return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool PlayerController::IsUp(ControllerButton button) const
{
	return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool PlayerController::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}

int PlayerController::GetIndex()
{
	return pImpl->GetIndex();
}

int* PlayerController::GetControllerIds()
{
	return nullptr;
}
