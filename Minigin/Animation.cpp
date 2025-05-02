#include "Animation.h"
#include "ResourceManager.h"

namespace dae
{
	Animation::Animation(const std::string& path, int frames) 
		: m_Frames{ frames }
	{
		m_TextureSPtr = ResourceManager::GetInstance().LoadTexture(path);
		m_SizeX = m_TextureSPtr->GetSize().x;
		m_SizeY = m_TextureSPtr->GetSize().y;
	}

	dae::Rect Animation::GetFrameRect(int frame)
	{
		return Rect{ frame * m_SizeX, 0, m_SizeX, m_SizeY };
	}

}
