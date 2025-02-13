#pragma once
#include <string>
#include <typeinfo>

namespace dae
{
	class Component
	{
	public:
		Component() = default;
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

	private:	
		bool m_PendingDelete{ false };
	};
}
