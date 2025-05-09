#pragma once
#include "Component.h"
#include <glm.hpp>

namespace dae
{
	class GameObject;
	class Render2DComponent;
	class Animation;
	class Animation2DComponent final : public Component
	{
	public:
		Animation2DComponent() = delete;
		Animation2DComponent(float frameTime, GameObject* owner)
			: Component(owner)
			, m_FrameTime{ frameTime }
			{}
		~Animation2DComponent() = default;

		Animation2DComponent(const Animation2DComponent&) = delete;
		Animation2DComponent(Animation2DComponent&&) noexcept = delete;
		Animation2DComponent& operator=(const Animation2DComponent&) = delete;
		Animation2DComponent& operator=(Animation2DComponent&&) noexcept = delete;

		void Start() override;

		void Play(const std::string& texturePath, uint32_t firstFrame, uint32_t lastFrame, uint32_t totalFrames, bool loop = false);

		void SetFrameTime(float frameTime);

		bool IsPlaying() { return m_IsPlaying; }
		bool IsLooping() { return m_IsLooping; }

		void Update(float deltaTime) override;


	private:
		Render2DComponent*	m_RenderComponentPtr;
		glm::ivec2 m_FrameSize{};
		uint32_t m_FirstFrame{};
		uint32_t m_LastFrame{};
		uint32_t m_CurrentFrame{};
		float m_FrameTime{};
		float m_Time{};
		bool m_IsPlaying{ false };
		bool m_IsLooping{ false };
	};
}