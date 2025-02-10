#pragma once

class Component
{
public:
	Component() = default;
	virtual ~Component() = 0;

	Component(const Component&) = delete;
	Component(Component&&) noexcept = delete;
	Component& operator=(const Component&) = delete;
	Component& operator=(Component&&) noexcept = delete;
	
	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate(float deltaTime) = 0;
	virtual void Render(float x, float y) const = 0;

	void Delete();
	bool PendingDelete() const;

private:
	bool m_PendingDelete{ false };
};
