#include <SDL_ttf.h>
#include <stdexcept>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

using namespace dae;

TextComponent::TextComponent(std::shared_ptr<Font> font) :
	m_RenderComponentSPtr{ std::make_shared<Render2DComponent>() },
	m_FontSPtr{ font }
{
	SetText(" ");
	Update(.0f);
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetColor(SDL_Color color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}

void TextComponent::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SetColor({ r, g, b, a });
}

std::string TextComponent::GetText() const
{
	return m_Text;
}

void TextComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_FontSPtr->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_RenderComponentSPtr->SetTexture(std::make_shared<Texture2D>(texture));
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render(float x, float y) const
{
	m_RenderComponentSPtr->Render(x, y);
}
