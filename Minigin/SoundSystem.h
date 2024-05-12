#pragma once
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include "Structs.h"

namespace dae {
	class AudioClip;
	class SoundSystem
	{
	public:
		SoundSystem();

		virtual int AddSound(std::string loc);
		virtual void Play(int id, int volume, bool looping = false);
		virtual void StopAll();
		virtual void Mute();

		~SoundSystem();

	private:
		void Initialize();
		void CheckQueue();

		std::vector<std::shared_ptr<AudioClip>> m_Clips{};
		std::vector<Sound> m_ToBePlayed{};
		std::thread m_Thread{};
		std::mutex m_Mutex{};

		bool m_Active = true;
		bool m_Muted = false;
	};

	class NullSoundSystem : public SoundSystem
	{
		virtual int AddSound(std::string) override { return -1; }
		virtual void Play(int, int, bool) override {}
		virtual void StopAll() override {}
		virtual void Mute() override {}
	};
}
