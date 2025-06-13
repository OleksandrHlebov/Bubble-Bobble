#pragma once
#include <memory>
#include "PlayerType.h"

namespace dae
{
	class GameObject;
	class PlayerState
	{
	public:
		PlayerState(const PlayerType& type, GameObject* player) 
			: m_Player	{ player }
			, m_Type	{ type }
			{}
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
		const PlayerType& GetType() { return m_Type; }

		bool m_CanTransition{ true };
	private:
		GameObject* m_Player;
		const PlayerType& m_Type;
	};
}