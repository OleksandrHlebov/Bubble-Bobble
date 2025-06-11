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

		bool CanTransition() { return m_CanTransition; }

		void ForceAllowTransition() { m_CanTransition = true; };

	protected:
		GameObject* GetPlayer() { return m_Player; }

		bool m_CanTransition{ true };
	private:
		GameObject* m_Player;
	};
}