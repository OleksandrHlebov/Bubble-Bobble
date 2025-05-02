#pragma once
#include <string>
#include <memory>
#include <SDL_pixels.h>
#include "Render2DComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public Component
	{
	public:
		TextComponent(std::shared_ptr<Font> font, GameObject* owner);
		 
		 TextComponent() = delete;
		~TextComponent() = default;

		TextComponent(const TextComponent&) = delete;
		TextComponent(TextComponent&&) noexcept = delete;
		TextComponent& operator=(const TextComponent&) = delete;
		TextComponent& operator=(TextComponent&&) noexcept = delete;

		void Start() override;

		void SetColor(SDL_Color color);
		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		void SetText(const std::string& text);
		std::string GetText() const;

		void SetFont(std::shared_ptr<Font> font);
		std::shared_ptr<Font> GetFont();

		void Update(float deltaTime) override;

		void Render() const override;

	private:
		// font can be shared between multiple objects and it's not supposed to be deleted while in use
		// hence the use of shared_ptr
		std::shared_ptr<Font> m_FontSPtr;

		Render2DComponent* m_RenderComponentPtr;

		std::string	m_Text{};
		SDL_Color	m_Color{ 255, 255, 255, 255 };

		bool m_NeedsUpdate{ true };
	};
}