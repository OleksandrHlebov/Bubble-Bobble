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

	void Animation2DComponent::Play(const std::string& texturePath, uint32_t firstFrame, uint32_t lastFrame, uint32_t totalFrames, bool loop, uint32_t loops)
	{
		m_RenderComponentPtr->SetTexture(texturePath);
		PlayCurrent(firstFrame, lastFrame, totalFrames, loop, loops);
	}

	void Animation2DComponent::Play(std::shared_ptr<Texture2D> texture, uint32_t firstFrame, uint32_t lastFrame, uint32_t totalFrames, bool loop, uint32_t loops)
	{
		m_RenderComponentPtr->SetTexture(texture);
		PlayCurrent(firstFrame, lastFrame, totalFrames, loop, loops);
	}

	void Animation2DComponent::PlayCurrent(uint32_t firstFrame, uint32_t lastFrame, uint32_t totalFrames, bool loop, uint32_t loops)
	{
		assert(totalFrames != 0);
		m_FrameSize = m_RenderComponentPtr->GetDimensions();
		m_FrameSize.x /= totalFrames;
		m_TotalFrames = totalFrames;
		m_RenderComponentPtr->SelectSection(firstFrame * m_FrameSize.x, 0, m_FrameSize.x, m_FrameSize.y);
		m_FirstFrame = firstFrame;
		m_LastFrame = lastFrame;
		m_CurrentFrame = firstFrame;
		m_IsLooping = loop;
		m_IsPlaying = true;
		m_TotalLoops = loops;
		m_CurrentLoop = 0;
	}

	void Animation2DComponent::SetFrameTime(float frameTime)
	{
		m_FrameTime = frameTime;
	}

	void Animation2DComponent::Update(float deltaTime)
	{
		if (m_FrameTime <= m_Time)
		{
			if (m_CurrentFrame == m_LastFrame)
			{
				if (!IsLooping() || m_CurrentLoop >= m_TotalLoops - 1)
				{
					--m_CurrentFrame;
					Stop();
				}
				else
				{
					++m_CurrentLoop;
				}
			}
				
			m_CurrentFrame = std::max(++m_CurrentFrame % (m_LastFrame + 1), m_FirstFrame);
			m_RenderComponentPtr->SelectSection(m_CurrentFrame * m_FrameSize.x, 0, m_FrameSize.x, m_FrameSize.y);
			m_Time -= m_FrameTime;
		}

		m_Time += deltaTime * IsPlaying();
	}

	void Animation2DComponent::Stop()
	{
		m_IsPlaying = false;
		GameEvent::Dispatch<OnAnimationFinished>(this);
	}
}
