#pragma once
#include <string>
#include <utility>
#include <memory>
#include "Ability.h"

namespace dae
{
	struct PlayerType final
	{
		PlayerType() = default;
		explicit PlayerType(std::pair<std::string, int> idle
							, std::pair<std::string, int> walking
							, std::pair<std::string, int> jumping
							, std::pair<std::string, int> falling
							, std::pair<std::string, int> dying
							, std::pair<std::string, int> attack
							, std::unique_ptr<Ability>&& abilityPtr)
			: IdleAnim	{ idle }
			, WalkingAnim	{ walking }
			, JumpingAnim	{ jumping }
			, FallingAnim	{ falling }
			, DyingAnim	{ dying }
			, AttackAnim	{ attack }
			, AbilityPtr	{ std::move(abilityPtr) }
		{
		}
		const std::pair<std::string, int>	IdleAnim;
		const std::pair<std::string, int>	WalkingAnim;
		const std::pair<std::string, int>	JumpingAnim;
		const std::pair<std::string, int>	FallingAnim;
		const std::pair<std::string, int>	DyingAnim;
		const std::pair<std::string, int>	AttackAnim;
		std::unique_ptr<Ability>			AbilityPtr;
	};
}