#pragma once
#include <memory>
#include "TextComponent.h"

namespace dae
{
	class FPSComponent final : public Component
	{
	public:
		FPSComponent(GameObject* owner);
		~FPSComponent() = default;

		FPSComponent(const FPSComponent&) = delete;
		FPSComponent(FPSComponent&&) noexcept = delete;
		FPSComponent& operator=(const FPSComponent&) = delete;
		FPSComponent& operator=(FPSComponent&&) noexcept = delete;

		void Update(float deltaTime) override;

		void Render() const override;

	private:
		TextComponent* m_TextComponentPtr;

		float	m_Timer{};
		int		m_FrameCount{};
	};
}