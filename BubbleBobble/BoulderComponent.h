#pragma once
#include "Component.h"
#include "GameEvent.h"

namespace dae
{
	class BoulderComponent final : public Component
	{
	public:
		BoulderComponent() = delete;
		BoulderComponent(const glm::vec3& direction, GameObject* creator, GameObject* owner)
			: Component(owner)
			, m_Direction	{ direction }
			, m_Creator		{ creator }
			{}
		~BoulderComponent() = default;
		
		BoulderComponent(const BoulderComponent&) 				= delete;
		BoulderComponent(BoulderComponent&&) noexcept 			= delete;
		BoulderComponent& operator=(const BoulderComponent&) 	 	= delete;
		BoulderComponent& operator=(BoulderComponent&&) noexcept 	= delete;

		void Start() override;

		void Update(float deltaTime) override;

		void End() override;

		void Break();

		void HandleOverlap(GameEvent*);
		void HandleEndOfLife(GameEvent*);

	private:
		EventHandler m_OverlapHandler{ std::bind(&BoulderComponent::HandleOverlap, this, std::placeholders::_1) };
		EventHandler m_EndOfLifeHandler{ std::bind(&BoulderComponent::HandleEndOfLife, this, std::placeholders::_1) };
		GameObject* m_Creator;
		const glm::vec3 m_Direction;
		const float m_Speed{ 50.f };
		bool m_IsBroken{};

	};
}