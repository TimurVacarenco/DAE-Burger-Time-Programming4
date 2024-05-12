#pragma once
#include <string>
#include <functional>

namespace dae
{
	class Minigin
	{
	public:

		void Initialize();

		virtual void LoadGame() = 0;
		virtual void Cleanup();
		void Run();

		Minigin() = default;
		~Minigin() = default;
		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
	private:
		const float m_FixedTimeStep = 0.2f;
		const int MsPerFrame = 16;
	};
}