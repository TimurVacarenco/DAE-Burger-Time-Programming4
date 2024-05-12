#pragma once
#include "EnumClasses.h"

namespace dae
{
	class Observer;
	class GameObject;

	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
	private:
		Observer* m_Observers[100]{};
		int m_NumOfObservers{};
	protected:
		void Notify(const GameObject* object, Event event);
	};
}
