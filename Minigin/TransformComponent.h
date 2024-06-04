#pragma once

#include "BaseComponent.h"
#include "Structs.h"
namespace dae
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent(GameObject* obj);

		const Vector3& GetLocalPosition() const;
		const Vector3& GetWorldPosition();

		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const Vector3& pos);
		void SetDirty();

		void Update(float) override {};
		void FixedUpdate(float) override {};
	private:
		void UpdateWorldPosition();

		Vector3 m_LocalPosition{};
		Vector3 m_WorldPosition{};
		bool m_IsDirty = false;
	};
}
