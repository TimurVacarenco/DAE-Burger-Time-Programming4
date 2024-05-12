#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(GameObject* object);
		void RemoveAll();

		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void Render() const;

		std::string& GetName() { return m_Name; }
		std::vector<std::shared_ptr<GameObject>>& GetObjects() { return m_Objects; }
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name);
		void DeleteObjects();

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector<GameObject*> m_ToRemove{};

		static unsigned int m_idCounter;
	};

}
