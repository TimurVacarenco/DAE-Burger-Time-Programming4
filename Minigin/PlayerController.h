#pragma once
#include <vector>
#include "EnumClasses.h"
namespace dae
{
	class PlayerController final
	{
		class PlayerControllerImpl;
		PlayerControllerImpl* pImpl;
		//static int* connectedIds;
	public:
		void Update();

		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;
		int GetIndex();

		static int* GetControllerIds();
		explicit PlayerController(int controllerIndex);
		~PlayerController();
	};
}

