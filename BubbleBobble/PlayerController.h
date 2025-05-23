#pragma once
#include "Controller.h"

namespace dae
{
	class PlayerState;
	class InputAction;
	class GameObject;
	// make 2 separate player controllers for different input
	// to avoid making player input mapping system
	// gamepad player controller can be used for multiple players
	class PlayerController : public Controller
	{
	public:
		PlayerController() = delete;
		PlayerController(GameObject* owner);
		PlayerController(bool useGamepad, GameObject* owner);
		virtual ~PlayerController();

		PlayerController(const PlayerController&)					= delete;
		PlayerController(PlayerController&&) noexcept				= delete;
		PlayerController& operator=(const PlayerController&)		= delete;
		PlayerController& operator=(PlayerController&&) noexcept	= delete;

		void Start() override;

		void Update(float deltaTime) override;

		void End() override;

	private:
		InputAction* m_IAMoveRight;
		InputAction* m_IAMoveLeft;

		InputAction* m_IAMoveRightLeft;
		InputAction* m_IADamageSelf;
		InputAction* m_IABurp;

		InputAction* m_IAJump;

		std::unique_ptr<PlayerState> m_PlayerState;
	};
}