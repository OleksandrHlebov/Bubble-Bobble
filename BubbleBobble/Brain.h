#pragma once
#include "Component.h"
#include "AIType.h"
#include <memory>

namespace dae
{
	class AIState;
	class Brain final : public Component
	{
	public:
		Brain() = delete;
		Brain(const AIType& type, GameObject* owner);
		~Brain();

		Brain(const Brain&) = delete;
		Brain(Brain&&) noexcept = delete;
		Brain& operator=(const Brain&) = delete;
		Brain& operator=(Brain&&) noexcept = delete;

		void Update(float deltaTime) override;

		void End() override;

	private:
		const AIType& m_Type;
		std::unique_ptr<AIState> m_State;
	};
}