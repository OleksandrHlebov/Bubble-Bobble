#pragma once
#include <string>

namespace dae
{
	struct AIType
	{
		explicit AIType(float speed, const std::string& walkingTexturePath, const std::string& trappedTexturePath)
			: Speed{ speed }
			, WalkingTexturePath{ walkingTexturePath }
			, TrappedTexturePath{ trappedTexturePath }
			{}
		const float Speed;
		const std::string WalkingTexturePath;
		const std::string TrappedTexturePath;
	};
}