#pragma once
#include <memory>
#include "Texture2D.h"
#include "Datatypes.h"

namespace dae
{
	class Animation final
	{
	public:
		Animation(const std::string& path, int frames);
		~Animation() = default;
		
		Animation(const Animation&) 				= delete;
		Animation(Animation&&) noexcept 			= delete;
		Animation& operator=(const Animation&) 	 	= delete;
		Animation& operator=(Animation&&) noexcept 	= delete;

		Rect GetFrameRect(int frame);

	private:
		std::shared_ptr<Texture2D> m_TextureSPtr;
		const int m_Frames;
		int m_SizeY;
		int m_SizeX;
	};
}