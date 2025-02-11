#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"

using namespace dae;

void RenderComponent::Render(float x, float y) const
{
	Renderer::GetInstance().RenderTexture(*m_TextureSPtr, x, y);
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_TextureSPtr = ResourceManager::GetInstance().LoadTexture(filename);
}

void RenderComponent::SetTexture(std::shared_ptr<Texture2D> textureSPtr)
{
	m_TextureSPtr = textureSPtr;
}
