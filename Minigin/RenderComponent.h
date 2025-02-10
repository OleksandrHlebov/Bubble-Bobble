#pragma once
#include "Component.h"
#include <memory>
#include <string>

namespace dae
{
	class Texture2D;
	class RenderComponent final : public Component
	{
	public:
		RenderComponent() = default;
		~RenderComponent() = default;

		RenderComponent(const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) noexcept = delete;
		RenderComponent& operator=(const RenderComponent&) = delete;
		RenderComponent& operator=(RenderComponent&&) noexcept = delete;

		void Update(float deltaTime) override;

		void FixedUpdate(float deltaTime) override;

		void Render(float x, float y) const override;

		void SetTexture(const std::string& filename);

	private:
		std::shared_ptr<dae::Texture2D> m_TextureSPtr;
	};
}