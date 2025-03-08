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

		uint32_t GetPlayerIndex() { return m_PlayerIndex; }

		void Start() override;

	private:
		InputAction* m_IAMoveUp;
		InputAction* m_IAMoveDown;
		InputAction* m_IAMoveRight;
		InputAction* m_IAMoveLeft;

		inline static uint32_t m_PlayerCount{};
		uint32_t m_PlayerIndex;
	};
}