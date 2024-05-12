#pragma once
enum class Event;
class GameObject;

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void OnNotify(const GameObject* obj, Event event) = 0;
	};
}
