#pragma once
namespace dae {
	class GameObject;
	class BaseComponent
	{
	public:
		~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void FixedUpdate(float deltaTime) = 0;
		virtual void Update(float deltaTime) = 0;
	private:
		GameObject* m_Owner;
	protected:
		explicit BaseComponent(GameObject* owner) : m_Owner(owner) {};
		GameObject* GetOwner() const { return m_Owner; }
	};

}