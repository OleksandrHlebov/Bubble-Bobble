#pragma once
#include "Ability.h"

namespace dae
{
	class BoulderRolling final : public Ability
	{
	public:
		BoulderRolling() = default;

		void ExecuteOn(GameObject* gameObject) override;

	private:

	};
}