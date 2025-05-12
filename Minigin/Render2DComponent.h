#pragma once
#include "Component.h"
#include <memory>
#include <string>
#include <glm.hpp>
#include "Datatypes.h"

namespace dae
{
	class Transform;
	class Texture2D;
	class Render2DComponent final : public Component
	{
	public:
		Render2DComponent(GameObject* owner);
		~Render2DComponent() = default;

		Render2DComponent(const Render2DComponent&) = delete;
		Render2DComponent(Render2DComponent&&) noexcept = delete;
		Render2DComponent& operator=(const Render2DComponent&) = delete;
		Render2DComponent& operator=(Render2DComponent&&) noexcept = delete;

		void Start() override;

		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);

		void SelectSection(int x, int y, int width, int height);

		void Flip(bool flip) { m_IsFlipped = flip; }

		glm::ivec2 GetDimensions();

	private:
		Transform* m_TransformPtr{};
		std::shared_ptr<Texture2D> m_TextureSPtr{};
		Rect m_Source;
		bool m_IsFlipped{};

	};
}