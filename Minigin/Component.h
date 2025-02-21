#pragma once
#include <string>
#include <typeinfo>

namespace dae
{
	class GameObject;
	class Component
	{
	public:
		virtual ~Component() = 0;

		Component(const Component&) = delete;
		Component(Component&&) noexcept = delete;
		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) noexcept = delete;

		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void Render(float x, float y) const;

		void Delete();
		bool IsPendingDelete() const;

		const GameObject* GetOwner() const;

	protected:
		Component(GameObject* owner);

	private:	
		const GameObject* m_OwnerPtr;

		bool m_PendingDelete{ false };
	};
}
