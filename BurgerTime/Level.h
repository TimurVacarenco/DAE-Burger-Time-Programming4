#pragma once
namespace dae {
	class Scene;

	class Level
	{
	public:
		Level(Scene& scene);
		void Initialize(Scene& scene);
	};
}