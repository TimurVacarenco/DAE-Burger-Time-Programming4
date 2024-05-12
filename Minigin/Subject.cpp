#include "Subject.h"
#include "Observer.h"

void dae::Subject::AddObserver(Observer* observer)
{
	bool added = false;
	for (int x{}; x < m_NumOfObservers; ++x)
	{
		if (m_Observers[x] == observer)
		{
			added = true;
		}
	}
	if (!added)
	{
		m_Observers[m_NumOfObservers] = observer;
		++m_NumOfObservers;
	}
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	for (int x{}; x < m_NumOfObservers; ++x)
	{
		if (m_Observers[x] == observer)
		{
			m_Observers[x] = m_Observers[m_NumOfObservers - 1];
			m_Observers[m_NumOfObservers - 1] = nullptr;
			--m_NumOfObservers;
		}
	}
}

void dae::Subject::Notify(const GameObject* object, Event event)
{
	for (int x{}; x < m_NumOfObservers; ++x)
	{
		m_Observers[x]->OnNotify(object, event);
	}
}
