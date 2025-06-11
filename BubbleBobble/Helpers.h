#pragma once
#include <memory>

namespace dae
{
	template<typename StateType>
	void TransitionState(std::unique_ptr<StateType>& owningState, std::unique_ptr<StateType> newState)
	{
		if (owningState->CanTransition())
		{
			owningState->OnExit();
			owningState = std::move(newState);
			owningState->OnEnter();
		}
	}
}