#include "Animation2DComponent.h"
#include "GameObject.h"
#include "Render2DComponent.h"
#include <algorithm>
#include <cassert>

namespace dae
{
	void Animation2DComponent::Start()
	{
		m_RenderComponentPtr = GetOwner()->GetComponent<Render2DComponent>();
	}

	void Animation2DComponent::Play(const std::string& texturePath, uint32_t firstFrame, uint32_t lastFrame, uint32_t totalFrames, bool loop)
	{
		m_RenderComponentPtr->SetTexture(texturePath);
		StartPlay(firstFrame, lastFrame, totalFrames, loop);
	}

	void Animation2DComponent::Play(std::shared_ptr<Texture2D> texture, uint32_t firstFrame, uint32_t lastFrame, uint32_t totalFrames, bool loop /*= false*/)
	{
		m_RenderComponentPtr->SetTexture(texture);
		StartPlay(firstFrame, lastFrame, totalFrames, loop);
	}

	void Animation2DComponent::StartPlay(uint32_t firstFrame, uint32_t lastFrame, uint32_t totalFrames, bool loop)
	{
		assert(totalFrames != 0);
		m_FrameSize = m_RenderComponentPtr->GetDimensions();
		m_FrameSize.x /= totalFrames;
		m_RenderComponentPtr->SelectSection(firstFrame * m_FrameSize.x, 0, m_FrameSize.x, m_FrameSize.y);
		m_FirstFrame = firstFrame;
		m_LastFrame = lastFrame;
		m_CurrentFrame = firstFrame;
		m_IsLooping = loop;
		m_IsPlaying = true;
	}

	void Animation2DComponent::SetFrameTime(float frameTime)
	{
		m_FrameTime = frameTime;
	}

	void Animation2DComponent::Update(float deltaTime)
	{
		if (m_FrameTime <= m_Time)
		{
			if (m_CurrentFrame == m_LastFrame && !IsLooping())
			{
				m_IsPlaying = false;
				--m_CurrentFrame;
			}
				
			m_CurrentFrame = std::max(++m_CurrentFrame % (m_LastFrame + 1), m_FirstFrame);
			m_RenderComponentPtr->SelectSection(m_CurrentFrame * m_FrameSize.x, 0, m_FrameSize.x, m_FrameSize.y);
			m_Time -= m_FrameTime;
		}

		m_Time += deltaTime * IsPlaying();
	}

}
