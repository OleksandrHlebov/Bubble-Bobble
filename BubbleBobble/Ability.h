#pragma once

namespace dae
{
	class GameObject;
	class Ability
	{
	public:
		virtual ~Ability() = 0 {}

		virtual void ExecuteOn(GameObject* gameObject) = 0;

	protected:
		Ability() = default;

	};
	
	class NullAbility final : public Ability
	{
	public:
		NullAbility() = default;

		void ExecuteOn(GameObject*) {}

	private:
	};
}
