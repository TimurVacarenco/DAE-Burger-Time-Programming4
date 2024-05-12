#include "HealthComponent.h"

void dae::HealthComponent::Hit(int amt)
{
	m_Lives -= amt;
	if (m_Lives == 0)
	{
		Notify(GetOwner(), Event::ON_DEATH);
	}
	else
		Notify(GetOwner(), Event::ON_HIT);
}
