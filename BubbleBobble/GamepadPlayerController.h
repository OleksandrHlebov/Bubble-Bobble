#pragma once
#include "Controller.h"

namespace dae
{
	class InputAction;
	class GameObject;
	// make 2 separate player controllers for different input
	// to avoid making player input mapping system
	// gamepad player controller can be used for multiple players
	class GamepadPlayerController : public Controller
	{
	public:
		GamepadPlayerController() = delete;
		GamepadPlayerController(GameObject* owner);
		virtual ~GamepadPlayerController();

		GamepadPlayerController(const GamepadPlayerController&)					= delete;
		GamepadPlayerController(GamepadPlayerController&&) noexcept				= delete;
		GamepadPlayerController& operator=(const GamepadPlayerController&)		= delete;
		GamepadPlayerController& operator=(GamepadPlayerController&&) noexcept	= delete;

		void Start() override;

	private:
		InputAction* m_IAMoveUp;
		InputAction* m_IAMoveDown;
		InputAction* m_IAMoveRight;
		InputAction* m_IAMoveLeft;

		InputAction* m_IAMoveUpDown;
		InputAction* m_IAMoveRightLeft;
		InputAction* m_IADamageSelf;
		InputAction* m_IAPickUp;
	};
}