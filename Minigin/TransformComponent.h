#pragma once
#include <glm/glm.hpp>

#include "BaseComponent.h"

namespace dae
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent(GameObject* obj);

		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();

		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3& pos);
		void SetDirty();

		void Update(float) override {};
		void FixedUpdate(float) override {};
	private:
		void UpdateWorldPosition();

		glm::vec3 m_LocalPosition{};
		glm::vec3 m_WorldPosition{};
		bool m_IsDirty = false;
	};
}
