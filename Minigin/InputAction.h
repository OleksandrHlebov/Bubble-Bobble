#pragma once
#include "Command.h"
#include "GameObject.h"
#include <memory>
#include "Keybind.h"
#include <map>

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
		InputAction(Command* command, Keybind keybind, BindTrigger trigger);
		~InputAction() = default;

		InputAction(const InputAction&) = delete;
		InputAction(InputAction&&) noexcept = delete;
		InputAction& operator=(const InputAction&) = delete;
		InputAction& operator=(InputAction&&) noexcept = delete;

		void Bind(Command* command, BindTrigger trigger);

		void UnBind(BindTrigger trigger);

		void Delete();

		void ChangeKeybind(Keybind&& keybind)
		{
			m_Keybind = std::move(keybind);
		}

		float GetValue() { return m_Value; }

		float GetDeltaTime() { return m_DeltaTime; }

		void Execute(BindTrigger trigger, float deltaTime, float value = 1.f);

		Keybind GetKeybind() { return m_Keybind; }

		bool operator==(const InputAction* right)
		{
			return this == right;
		}

	private:
		std::map<BindTrigger,std::unique_ptr<Command>> m_TriggerBinds;
		Keybind m_Keybind{};
		float m_Value{};
		float m_DeltaTime{};
	};
}