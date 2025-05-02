#include "FPSComponent.h"
#include <sstream>
#include <iomanip>
#include "GameObject.h"

using namespace dae;

FPSComponent::FPSComponent(GameObject* owner) :
	Component(owner),
	m_TextComponentPtr{ owner->GetComponent<TextComponent>() }
{}

void FPSComponent::Update(float deltaTime)
{
	m_Timer += deltaTime;
	++m_FrameCount;
	if (m_Timer > 1.f)
	{
		float fps{ m_FrameCount / m_Timer };
		m_FrameCount = 0;
		m_Timer = .0f;

		std::stringstream buffer;
		buffer << "FPS: ";
		buffer << std::fixed << std::setprecision(1) << fps;

		m_TextComponentPtr->SetText(buffer.str());
		m_TextComponentPtr->Update(deltaTime);
	}
}

void dae::FPSComponent::Render() const
{
	m_TextComponentPtr->Render();
}

