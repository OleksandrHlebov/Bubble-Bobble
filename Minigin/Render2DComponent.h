#pragma once
#include "Component.h"
#include <memory>
#include <string>

namespace dae
{
	class Texture2D;
	class Render2DComponent final : public Component
	{
	public:
		Render2DComponent() = default;
		~Render2DComponent() = default;

		Render2DComponent(const Render2DComponent&) = delete;
		Render2DComponent(Render2DComponent&&) noexcept = delete;
		Render2DComponent& operator=(const Render2DComponent&) = delete;
		Render2DComponent& operator=(Render2DComponent&&) noexcept = delete;

		void Render(float x, float y) const override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> textureSPtr);

	private:
		std::shared_ptr<dae::Texture2D> m_TextureSPtr{};
	};
}