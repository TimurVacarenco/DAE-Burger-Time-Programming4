#pragma once
#include <memory>
namespace dae
{
	class BaseCommand
	{
	public:
		BaseCommand() {}
		virtual void SetActor(std::weak_ptr<GameObject> pGameObject) { m_pActor = pGameObject; };
		virtual ~BaseCommand() = default;
		virtual void Execute() = 0;
	protected:
		const std::weak_ptr<GameObject> GetActor() { return m_pActor; }
	private:
		std::weak_ptr<GameObject> m_pActor;
	};
}