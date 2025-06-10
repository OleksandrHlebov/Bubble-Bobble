#pragma once
#include <glm.hpp>

namespace dae
{
	inline float Cross2D(const glm::vec2& a, const glm::vec2& b)
	{
		return a.x * b.y - a.y * b.x;
	}
}