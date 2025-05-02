#pragma once
#include "Component.h"

namespace dae
{
	class GameObject;
	class Render2DComponent;
	class Animation;
	class Animation2DComponent final : public Component
	{
	public:
		Animation2DComponent() = delete;
		Animation2DComponent(GameObject* owner) 
			: Component(owner)
			{}
		~Animation2DComponent() = default;

		Animation2DComponent(const Animation2DComponent&) = delete;
		Animation2DComponent(Animation2DComponent&&) noexcept = delete;
		Animation2DComponent& operator=(const Animation2DComponent&) = delete;
		Animation2DComponent& operator=(Animation2DComponent&&) noexcept = delete;

		void Start() override;

		void Play(Animation* animation);

		void SetFrameTime(float frameTime);

		void Update(float deltaTime) override;

	private:
		Render2DComponent*	m_RenderComponentPtr;
		Animation* m_PlayingAnimation;
		float m_FrameTime{};
		float m_Time{};
		float m_CurrentFrame{};
	};
}