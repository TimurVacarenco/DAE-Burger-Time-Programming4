#pragma once
#include <memory>
#include <vector>
#include <string>
#include "TransformComponent.h"

enum class Tag;

namespace dae
{
	class BaseComponent;
	class Texture2D;

	class GameObject final 
	{
	public:
		GameObject() { m_Transform = AddComponent<TransformComponent>(); };
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		virtual void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;


		GameObject* GetParent();
		void SetParent(GameObject* parent, bool keepWorldPos);
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

		void SetTag(Tag tag);
		const Tag& GetTag() const;
		std::vector<GameObject*> GetChildren() const;

		TransformComponent* GetTransform();

		template <typename T>
		T* AddComponent()
		{
			if (std::is_base_of<BaseComponent, T>())
			{

				std::shared_ptr < T > ptr = std::make_shared<T>(this);
				m_Components.push_back(ptr);
				return ptr.get();
			}
			else return nullptr;
		}

		template <typename T>
		T* GetComponent() const
		{
			for (std::shared_ptr<BaseComponent> comp : m_Components)
			{
				if (dynamic_cast<T*>(comp.get()))
				{
					return (T*)comp.get();
				}

			}
			return nullptr;
		}

		template <typename T>
		std::vector<T*> GetComponents() const
		{
			std::vector<T*> comps{};
			for (std::shared_ptr<BaseComponent> comp : m_Components)
			{
				if (dynamic_cast<T*>(comp.get()))
				{
					comps.push_back((T*)comp.get());
				}
			}
			return comps;
		}

		template<typename T>
		void RemoveComponent()
		{
			for (auto it = m_Components.begin(); it < m_Components.end();)
			{
				if (typeid(**it) == typeid(T))
				{
					it = m_Components.erase(it);
				}
				else
				{
					++it;
				}
			}

		}
	private:
		GameObject* m_Parent = nullptr;
		std::vector<GameObject*> m_Children{};
		TransformComponent* m_Transform;
		std::vector<std::shared_ptr<BaseComponent>> m_Components{};
		Tag m_Tag{};
	};

}