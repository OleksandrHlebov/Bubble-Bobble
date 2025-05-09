#include "Render2DComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "Texture2D.h"

using namespace dae;

void Render2DComponent::Start()
{
	m_TransformPtr = GetOwner()->GetComponent<Transform>();
}

void dae::Render2DComponent::Render() const
{
	const glm::vec3& pos = m_TransformPtr->GetWorldPosition();
	const glm::vec3& scale = m_TransformPtr->GetScale();
	SDL_Rect source{ 
		static_cast<int>(m_Source.x), 
		static_cast<int>(m_Source.y),
		static_cast<int>(m_Source.width),
		static_cast<int>(m_Source.height) 
		};
	Renderer::GetInstance().RenderTexture(*m_TextureSPtr, RenderParams{ pos, scale, source, (m_IsFlipped) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE });
}

glm::ivec2 Render2DComponent::GetDimensions()
{
	return m_TextureSPtr->GetSize();
}

void Render2DComponent::SelectSection(int x, int y, int width, int height)
{
	m_Source = Rect{ x, y, width, height };
}

void Render2DComponent::SetTexture(const std::string& filename)
{
	SetTexture(ResourceManager::GetInstance().LoadTexture(filename));
}

void Render2DComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_TextureSPtr = texture;
	m_Source = Rect{ 0, 0, m_TextureSPtr->GetSize().x, m_TextureSPtr->GetSize().y };
}

Render2DComponent::Render2DComponent(GameObject* owner) :
	Component(owner)
{

}
