#include "Brain.h"
#include "AIState.h"
#include "Helpers.h"
#include "TrappedAIState.h"

dae::Brain::Brain(const AIType& type, GameObject* owner) 
	: Component(owner)
	, m_Type{ type }
	, m_State{ std::make_unique<AIState>(owner, m_Type) }
{

}

dae::Brain::~Brain() = default;

void dae::Brain::Update(float deltaTime)
{
	if (std::unique_ptr<AIState> state = m_State->Update(deltaTime))
	{
		dae::TransitionState(m_State, std::move(state));
	}
}

void dae::Brain::End()
{
	m_State->OnExit();
}

bool dae::Brain::TrapInBubble()
{
	return dae::TransitionState<AIState>(m_State, std::make_unique<TrappedAIState>(GetOwner(), m_Type));
}
