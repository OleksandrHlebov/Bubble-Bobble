#include "FPSComponent.h"
#include <sstream>
#include <iomanip>

using namespace dae;

FPSComponent::FPSComponent(std::shared_ptr<Font> font) :
	m_TextComponentSPtr{ std::make_shared<TextComponent>(font) }
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

		m_TextComponentSPtr->SetText(buffer.str());
		m_TextComponentSPtr->Update(deltaTime);
	}
}

void FPSComponent::Render(float x, float y) const
{
	m_TextComponentSPtr->Render(x, y);
}

