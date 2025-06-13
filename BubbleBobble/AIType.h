#pragma once
#include <string>
#include <memory>
#include "Ability.h"

namespace dae
{
	struct AIType
	{
		explicit AIType(float speed
						, std::pair<std::string, int> walkingTexturePath
						, std::pair<std::string, int> trappedTexturePath
						, std::pair<std::string, int> deadTexturePath
						, std::pair<std::string, int> treatTextureValue
						, Ability* abilityPtr)
			: Speed{ speed }
			, WalkingTextureAnim{ walkingTexturePath }
			, TrappedTextureAnim{ trappedTexturePath }
			, DeadTextureAnim	{ deadTexturePath }
			, TreatTextureValue	{ treatTextureValue }
			, AbilityPtr		{ abilityPtr }
			{}
		const float Speed;
		const std::pair<std::string, int>	WalkingTextureAnim;
		const std::pair<std::string, int>	TrappedTextureAnim;
		const std::pair<std::string, int>	DeadTextureAnim;
		const std::pair<std::string, int>	TreatTextureValue;
		Ability* AbilityPtr;
	};
}