#pragma once
#include <string>
#include <utility>
#include "Ability.h"

namespace dae
{
	class BubbleBlowing final : public Ability
	{
	public:
		BubbleBlowing() = default;

		void ExecuteOn(GameObject* gameObject) override;

	private:
		std::pair<std::string, int> m_BubbleAnim[2] { { "Textures/Bub_bubble.png", 7 }
													, { "Textures/Bob_bubble.png", 7 } };
	};
}
