#pragma once
#include <memory>
#include "TextComponent.h"

namespace dae
{
	class FPSComponent final : public Component
	{
	public:
		FPSComponent(std::shared_ptr<Font> font);
		~FPSComponent() = default;

		FPSComponent(const FPSComponent&) = delete;
		FPSComponent(FPSComponent&&) noexcept = delete;
		FPSComponent& operator=(const FPSComponent&) = delete;
		FPSComponent& operator=(FPSComponent&&) noexcept = delete;

		void Update(float deltaTime) override;

		void Render(float x, float y) const override;

	private:
		std::shared_ptr<TextComponent> m_TextComponentSPtr;

		float	m_Timer{};
		int		m_FrameCount{};
	};
}