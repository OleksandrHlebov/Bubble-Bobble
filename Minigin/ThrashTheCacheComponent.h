#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	class ThrashTheCacheComponent final : public Component
	{
	public:
		ThrashTheCacheComponent() = delete;
		ThrashTheCacheComponent(GameObject* owner) : Component(owner) {}
		~ThrashTheCacheComponent() = default;

		ThrashTheCacheComponent(const ThrashTheCacheComponent&) = delete;
		ThrashTheCacheComponent(ThrashTheCacheComponent&&) noexcept = delete;
		ThrashTheCacheComponent& operator=(const ThrashTheCacheComponent&) = delete;
		ThrashTheCacheComponent& operator=(ThrashTheCacheComponent&&) noexcept = delete;

		void RenderUI() override;

	private:
		void RenderExercise1();

		void RenderExercise2();

		std::vector<float> m_Ex1Results;
		std::vector<float> m_Ex2Results;
		std::vector<float> m_Ex2ResultsAlt;

		int m_Ex1Samples{ 10 };
		int m_Ex2Samples{ 10 };
	};
}
