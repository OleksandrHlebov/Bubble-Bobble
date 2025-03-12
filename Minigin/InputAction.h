#pragma once
#include "Command.h"
#include "GameObject.h"
#include <memory>
#include <any>
#include "Keybind.h"

namespace dae
{
	enum class BindTrigger : uint8_t
	{
		Pressed,
		Held,
		Released
	};

	class InputAction final
	{
	public:
		InputAction(Command* command, Keybind keybind, BindTrigger trigger) 
			: m_Keybind{ keybind }
		{
			command->Initialize(this);
			switch (trigger)
			{
			case BindTrigger::Pressed:
				m_PressedPtr.reset(command);
				break;
			case BindTrigger::Held:
				m_HeldPtr.reset(command);
				break;
			case BindTrigger::Released:
				m_ReleasedPtr.reset(command);
				break;
			}
		}
		~InputAction() = default;

		InputAction(const InputAction&) = delete;
		InputAction(InputAction&&) noexcept = delete;
		InputAction& operator=(const InputAction&) = delete;
		InputAction& operator=(InputAction&&) noexcept = delete;

		void Bind(Command* command, BindTrigger trigger)
		{
			switch (trigger)
			{
			case BindTrigger::Pressed:
				m_PressedPtr.reset(command);
				break;
			case BindTrigger::Held:
				m_HeldPtr.reset(command);
				break;
			case BindTrigger::Released:
				m_ReleasedPtr.reset(command);
				break;
			}
		}

		void UnBind(BindTrigger trigger)
		{
			switch (trigger)
			{
			case BindTrigger::Pressed:
				m_PressedPtr.reset(nullptr);
				break;
			case BindTrigger::Held:
				m_HeldPtr.reset(nullptr);
				break;
			case BindTrigger::Released:
				m_ReleasedPtr.reset(nullptr);
				break;
			}
		}

		void ChangeKeybind(Keybind&& keybind)
		{
			m_Keybind = std::move(keybind);
		}

		float GetValue() { return m_Value; }

		float GetDeltaTime() { return m_DeltaTime; }

		void ExecutePressed	(float deltaTime, float value = 1.f);
		void ExecuteHeld	(float deltaTime, float value = 1.f);
		void ExecuteReleased(float deltaTime, float value = 1.f);

		Keybind GetKeybind() { return m_Keybind; }

	private:
		std::unique_ptr<Command> m_PressedPtr	{};
		std::unique_ptr<Command> m_HeldPtr		{};
		std::unique_ptr<Command> m_ReleasedPtr	{};
		Keybind m_Keybind{};
		float m_Value{};
		float m_DeltaTime{};
	};
}