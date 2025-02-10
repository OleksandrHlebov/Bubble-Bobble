#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"

using namespace dae;

void RenderComponent::Update(float)
{
}

void RenderComponent::FixedUpdate(float)
{
}

void RenderComponent::Render(float x, float y) const
{
	Renderer::GetInstance().RenderTexture(*m_TextureSPtr, x, y);
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_TextureSPtr = ResourceManager::GetInstance().LoadTexture(filename);
}
