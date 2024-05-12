
#include "ServiceLocator.h"

dae::SoundSystem* dae::ServiceLocator::m_SSInstance{};
dae::NullSoundSystem dae::ServiceLocator::m_DefaultSS{};

void dae::ServiceLocator::DestroySoundSystem()
{
	delete m_SSInstance;
	m_SSInstance = nullptr;
}

