#include "Render2DComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"

using namespace dae;

void Render2DComponent::Render(float x, float y) const
{
	Renderer::GetInstance().RenderTexture(*m_TextureSPtr, x, y);
}

void Render2DComponent::SetTexture(const std::string& filename)
{
	m_TextureSPtr = ResourceManager::GetInstance().LoadTexture(filename);
}

void Render2DComponent::SetTexture(std::shared_ptr<Texture2D> textureSPtr)
{
	m_TextureSPtr = textureSPtr;
}
