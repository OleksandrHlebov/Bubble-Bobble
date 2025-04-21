#pragma once
#include "Controller.h"

namespace dae
{
	class InputAction;
	class GameObject;
	// make 2 separate player controllers for different input
	// to avoid making player input mapping system
	class KeyboardPlayerController : public Controller
	{
	public:
		KeyboardPlayerController() = delete;
		KeyboardPlayerController(GameObject* owner);
		virtual ~KeyboardPlayerController();

		KeyboardPlayerController(const KeyboardPlayerController&) = delete;
		KeyboardPlayerController(KeyboardPlayerController&&) noexcept = delete;
		KeyboardPlayerController& operator=(const KeyboardPlayerController&) = delete;
		KeyboardPlayerController& operator=(KeyboardPlayerController&&) noexcept = delete;

		void Start() override;

	private:
		InputAction* m_IAMoveUp;
		InputAction* m_IAMoveDown;
		InputAction* m_IAMoveRight;
		InputAction* m_IAMoveLeft;

		InputAction* m_IAJump;

		InputAction* m_IADamageSelf;
	};
}