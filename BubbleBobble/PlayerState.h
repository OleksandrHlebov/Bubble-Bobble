#pragma once
#include <memory>

namespace dae
{
	class GameObject;
	class PlayerState
	{
	public:
		PlayerState(GameObject* player) : m_Player{ player } {}
		virtual ~PlayerState() {}

		PlayerState(const PlayerState&) = delete;
		PlayerState(PlayerState&&) noexcept = delete;
		PlayerState& operator=(const PlayerState&) = delete;
		PlayerState& operator=(PlayerState&&) noexcept = delete;

		virtual void OnEnter() {  }
		virtual std::unique_ptr<PlayerState> Update(float deltaTime);
		virtual void OnExit() {  }

		static void TransitionState(std::unique_ptr<PlayerState>& owningState, std::unique_ptr<PlayerState> newState);

	protected:
		GameObject* GetPlayer() { return m_Player; }

	private:
		GameObject* m_Player;
	};
}