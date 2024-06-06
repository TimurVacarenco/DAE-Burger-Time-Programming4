#pragma once
#include "SceneManager.h"
#include "Structs.h"
namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Add(const std::shared_ptr<GameObject>& object, int renderPriority);

		void Remove(GameObject* object);
		void RemoveAll();

		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void Render() const;

		void SetBounds(Rect bounds) { m_Bounds = bounds; }
		Rect GetBounds() const { return m_Bounds; }

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
		std::vector < std::shared_ptr<GameObject>> m_ObjectsFirst{};
		std::vector < std::shared_ptr<GameObject>> m_ObjectsSecond{};
		std::vector < std::shared_ptr<GameObject>> m_ObjectsThird{};
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector<GameObject*> m_ToRemove{};

		Rect m_Bounds;

		static unsigned int m_idCounter;
	};

}
