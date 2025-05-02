#include "Animation2DComponent.h"
#include "GameObject.h"
#include "Render2DComponent.h"

namespace dae
{
	void Animation2DComponent::Start()
	{
		m_RenderComponentPtr = GetOwner()->GetComponent<Render2DComponent>();
	}

	void Animation2DComponent::Play(Animation* animation)
	{
		m_CurrentFrame = 0;
		m_PlayingAnimation = animation;
	}

	void Animation2DComponent::SetFrameTime(float frameTime)
	{
		m_FrameTime = frameTime;
	}

	void Animation2DComponent::Update(float deltaTime)
	{
		if (m_FrameTime <= m_Time)
		{
			++m_CurrentFrame;
		}
		m_Time += deltaTime;
	}

}
