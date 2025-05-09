#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "ImguiRenderer.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	ImguiRenderer::GetInstance().Init(window);
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();
	ImguiRenderer::GetInstance().NewFrame();
	SceneManager::GetInstance().RenderUI();
	ImguiRenderer::GetInstance().Render();

	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const RenderParams& params) const
{
	glm::ivec2 texSize = texture.GetSize();
	SDL_Rect dst{};
	dst.x = static_cast<int>(params.position.x);
	dst.y = static_cast<int>(params.position.y);
	dst.w = static_cast<int>(params.scale.x) * texSize.x;
	dst.h = static_cast<int>(params.scale.y) * texSize.y;
	
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &params.src, &dst);
}

void dae::Renderer::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
