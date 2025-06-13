#pragma once
#include <memory>
#include <vector>
#include <string>

namespace dae { class Scene; }

namespace dae
{
	enum class GameMode
	{
		Solo,
		Duo,
		Versus
	};

	template<typename StateType>
	bool TransitionState(std::unique_ptr<StateType>& owningState, std::unique_ptr<StateType> newState)
	{
		if (owningState->CanTransition())
		{
			owningState->OnExit();
			owningState = std::move(newState);
			owningState->OnEnter();
			return true;
		}
		return false;
	}
	void ReadLevelLayout(const std::string& path, std::vector<bool>& destination);

	inline static const float ANIMATION_FRAMETIME{ .16f };

	void CreatePlayer0(Scene* scene, bool usesGamepad);
	void CreatePlayer1(Scene* scene);
	void CreatePlayerAsMaita(Scene* scene);
	void CreateScene(const std::string& path, GameMode gameMode);
}
