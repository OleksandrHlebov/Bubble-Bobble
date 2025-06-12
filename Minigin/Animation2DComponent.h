#pragma once
#include "Component.h"
#include <glm.hpp>
#include <memory>
#include "GameEvent.h"

namespace dae
{
	class Texture2D;
	class GameObject;
	class Render2DComponent;
	class Animation2DComponent final : public Component
	{
	public:
		struct OnAnimationFinished final : public GameEvent
		{
			OnAnimationFinished(Animation2DComponent* animComp) 
				: GameEvent("OnAnimationFinished")
				, AnimationComponent{ animComp }
				{}

			Animation2DComponent* const AnimationComponent;
		};

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

		void Play(const std::string& texturePath, uint32_t firstFrame, uint32_t lastFrame, uint32_t totalFrames, bool loop = false, uint32_t loops = std::numeric_limits<uint32_t>::max());
		void Play(std::shared_ptr<Texture2D> texture, uint32_t firstFrame, uint32_t lastFrame, uint32_t totalFrames, bool loop = false, uint32_t loops = std::numeric_limits<uint32_t>::max());
		void PlayCurrent(uint32_t firstFrame, uint32_t lastFrame, uint32_t totalFrames, bool loop, uint32_t loops = std::numeric_limits<uint32_t>::max());

		void SetFrameTime(float frameTime);
		bool GetFrameTime() { return m_FrameTime; }
		uint32_t GetTotalFrames() { return m_TotalFrames; }

		bool IsPlaying() { return m_IsPlaying; }
		bool IsLooping() { return m_IsLooping; }

		void Update(float deltaTime) override;


	private:

		Render2DComponent*	m_RenderComponentPtr;
		glm::ivec2 m_FrameSize{};
		uint32_t m_FirstFrame{};
		uint32_t m_LastFrame{};
		uint32_t m_CurrentFrame{};
		uint32_t m_TotalFrames{};
		uint32_t m_CurrentLoop{};
		uint32_t m_TotalLoops{};
		float m_FrameTime{};
		float m_Time{};
		bool m_IsPlaying{ false };
		bool m_IsLooping{ false };
	};
}