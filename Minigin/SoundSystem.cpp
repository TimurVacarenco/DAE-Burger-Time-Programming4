#include "SoundSystem.h"

#include <SDL_mixer.h>
#include <thread>

#include "AudioClip.h"

dae::SoundSystem::SoundSystem()
	:m_Clips{}
{
	Initialize();
}

dae::SoundSystem::~SoundSystem()
{
	Mix_CloseAudio();
	m_Active = false;
	m_Thread.join();
}

void dae::SoundSystem::Initialize()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Thread = std::thread(&dae::SoundSystem::CheckQueue, this);
}


int dae::SoundSystem::AddSound(std::string loc)
{
	for (int i{}; i << m_Clips.size(); ++i)
		if (m_Clips[i]->GetFileLoc() == loc)
			return i;

	m_Clips.push_back(std::make_shared<AudioClip>(loc));
	return (unsigned int)m_Clips.size() - 1;
}

void dae::SoundSystem::CheckQueue()
{

	while (m_Active)
	{
		while (m_ToBePlayed.size() > 0)
		{
			m_Mutex.lock();
			m_Clips[m_ToBePlayed.back().id]->Load();
			if (m_Clips[m_ToBePlayed.back().id]->IsLoaded())
				m_Clips[m_ToBePlayed.back().id]->Play(m_ToBePlayed.back().volume, m_ToBePlayed.back().looping);
			m_ToBePlayed.pop_back();
			m_Mutex.unlock();
		}
	}
}

void dae::SoundSystem::Play(int id, int volume, bool looping)
{
	m_ToBePlayed.push_back(Sound{ id,volume,looping });
}

void dae::SoundSystem::StopAll()
{
	Mix_HaltChannel(-1);
}

void dae::SoundSystem::Mute()
{
	m_Muted = !m_Muted;

	if (m_Muted)
		Mix_Volume(-1, 0);
	else
		Mix_Volume(-1, MIX_MAX_VOLUME);
}
