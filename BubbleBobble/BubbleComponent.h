#pragma once
#include "Component.h"
#include <glm.hpp>
#include "EventDispatcher.h"

namespace dae
{
	struct GameEvent;
	class BubbleComponent final : public Component
	{
	public:
		BubbleComponent() = delete;
		BubbleComponent(const glm::vec2 direction, GameObject* owner) 
			: Component(owner)
			, m_Direction{ direction } {}
		~BubbleComponent() = default;
		
		BubbleComponent(const BubbleComponent&) 				= delete;
		BubbleComponent(BubbleComponent&&) noexcept 			= delete;
		BubbleComponent& operator=(const BubbleComponent&) 	 	= delete;
		BubbleComponent& operator=(BubbleComponent&&) noexcept 	= delete;

		void Update(float deltaTime) override;

		void HandleStaticOverlap(GameEvent* event);
		void HandleDynamicOverlap(GameEvent* event);

		void Start() override;

		void End() override;

		float Speed{ 75.f };

	private:
		EventHandler m_StaticOverlapHandler	{ std::bind(&BubbleComponent::HandleStaticOverlap, this, std::placeholders::_1) };
		EventHandler m_DynamicOverlapHandler{ std::bind(&BubbleComponent::HandleDynamicOverlap, this, std::placeholders::_1) };
		glm::vec2 m_Direction;

	};
}