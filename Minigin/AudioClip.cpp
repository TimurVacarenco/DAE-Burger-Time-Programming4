#include "AudioClip.h"

#include <SDL_mixer.h>
#include <stdexcept>

class dae::AudioClip::AudioImpl
{
public:
	AudioImpl(std::string loc)
	{
		m_Chunk = Mix_LoadWAV(loc.c_str());
		if (m_Chunk == nullptr)
		{
			throw std::runtime_error(std::string("Failed to load AudioClip: ") + SDL_GetError());
		}
	}
	~AudioImpl()
	{
		Mix_FreeChunk(m_Chunk);
	}
	void Play(int volume, bool looping) const
	{
		if (m_Chunk) {
			Mix_VolumeChunk(m_Chunk, volume);
			if (looping)
				Mix_PlayChannel(-1, m_Chunk, -1);
			else
				Mix_PlayChannel(-1, m_Chunk, 0);
		}
	}
private:
	Mix_Chunk* m_Chunk{};
};

dae::AudioClip::AudioClip(std::string loc)
	:m_FileLoc{ loc }
{
}

dae::AudioClip::~AudioClip()
{
	delete pImpl;
}

void dae::AudioClip::Play(int volume, bool looping) const
{
	pImpl->Play(volume, looping);
}

void dae::AudioClip::Load()
{
	if (!pImpl)
		pImpl = new AudioImpl(m_FileLoc);
}

bool dae::AudioClip::IsLoaded() const
{
	return pImpl != nullptr;
}