#pragma once
#include <SDL.h>
#include <glm.hpp>
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	struct RenderParams
	{
		glm::vec3 position;
		glm::vec3 scale;
		SDL_Rect src;
		SDL_RendererFlip flip;
	};
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, const RenderParams& params) const;
		void DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		void DrawLine(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

