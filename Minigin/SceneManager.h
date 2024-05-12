#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void SetActiveScene(std::string sceneName);
		Scene& GetActiveScene() const { return *m_ActiveScene; }
		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void Render();
		void RemoveScene(Scene& scene);
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		Scene* m_ActiveScene = nullptr;
		Scene* m_ToRemove = nullptr;
	};
}
