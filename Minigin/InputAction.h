#pragma once
#include "Command.h"
#include "GameObject.h"
#include <memory>
#include "Keybind.h"
#include <map>
#include <limits>

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
		void UnBind();

		void Delete();

		void ChangeKeybind(Keybind&& keybind)
		{
			m_Keybind = std::move(keybind);
		}

		void LinkToDeviceIndex(uint32_t deviceIndex)
		{
			m_DeviceIndex = deviceIndex;
		}

		uint32_t GetDeviceIndex()
		{
			return m_DeviceIndex;
		}

		void Execute(BindTrigger trigger, float deltaTime);

		Keybind GetKeybind() { return m_Keybind; }

		bool operator==(const InputAction* right) const
		{
			return this == right;
		}

	private:
		std::map<BindTrigger,std::unique_ptr<Command>> m_TriggerBinds;
		Keybind m_Keybind{};
		uint32_t m_DeviceIndex{ std::numeric_limits<uint32_t>::max() };

	};
}