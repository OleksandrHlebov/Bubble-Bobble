#pragma once

namespace dae
{
	enum class RenderPriority
	{
		Background = -5,
		GameSpace = 0,
		Foreground = 5,
		UI = 6
	};
}