#pragma once
#include <string>

namespace dae
{
	struct AIType
	{
		explicit AIType(float speed, std::pair<std::string, int> walkingTexturePath, std::pair<std::string, int> trappedTexturePath, std::pair<std::string, int> deadTexturePath)
			: Speed{ speed }
			, WalkingTexturePath{ walkingTexturePath }
			, TrappedTexturePath{ trappedTexturePath }
			, DeadTexturePath	{ deadTexturePath }
			{}
		const float Speed;
		const std::pair<std::string, int> WalkingTexturePath;
		const std::pair<std::string, int> TrappedTexturePath;
		const std::pair<std::string, int> DeadTexturePath;
	};
}