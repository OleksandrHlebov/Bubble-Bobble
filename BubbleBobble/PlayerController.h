#pragma once
#include "Controller.h"
#include "EventDispatcher.h"
#include "PlayerType.h"

namespace dae
{
	class PlayerState;
	class InputAction;
	class GameObject;
	class PlayerController : public Controller
	{
	public:
		PlayerController() = delete;
		PlayerController(bool useGamepad, GameObject* owner);
		PlayerController(PlayerType&& type, GameObject* owner);
		PlayerController(PlayerType&& type, bool useGamepad, GameObject* owner);
		virtual ~PlayerController();

		PlayerController(const PlayerController&)					= delete;
		PlayerController(PlayerController&&) noexcept				= delete;
		PlayerController& operator=(const PlayerController&)		= delete;
		PlayerController& operator=(PlayerController&&) noexcept	= delete;

		void Start() override;

		void Update(float deltaTime) override;

		void End() override;

		void Attack();

		void HandleHealthChange(GameEvent*);

	private:
		EventHandler m_HealthChangedHandler{ std::bind(&PlayerController::HandleHealthChange, this, std::placeholders::_1) };

		InputAction* m_IAMoveRight;
		InputAction* m_IAMoveLeft;

		InputAction* m_IAMoveRightLeft;
		InputAction* m_IADamageSelf;
		InputAction* m_IABurp;

		InputAction* m_IAJump;

		InputAction* m_IAMenuLeft;
		InputAction* m_IAMenuRight;
		InputAction* m_IAMenuUp;
		InputAction* m_IAMenuDown;
		InputAction* m_IAMenuPress;

		PlayerType m_Type;
		std::unique_ptr<PlayerState> m_PlayerState;
	};
}