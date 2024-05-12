#include "Input.h"

void Input::AddController(int index)
{
	bool connected = false;
	for (std::unique_ptr<dae::PlayerController>& controller : m_Controllers)
	{
		if (controller->GetIndex() == index)
		{
			connected = true;
		}
	}
	if (!connected)
	{
		m_Controllers.push_back(std::make_unique<dae::PlayerController>(index));
	}
}

void Input::CheckControllers()
{
	int* ids = dae::PlayerController::GetControllerIds();
	for (int i{}; i < 4; i++)
	{
		if (ids[i] != -1)
		{
			AddController(ids[i]);
		}
	}
}
