#pragma once
#include <cinttypes>
#include <memory>
#include "glm.hpp"

namespace dae
{
	// own keybind implementation to allow
	// adjusting and remapping for other os
	class Gamepad
	{
	public:
		enum class Button : uint32_t
		{
			None = 0,
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			A = 0x1000,
			B = 0x2000,
			X = 0x4000,
			Y = 0x8000
		};

		enum class ValueProvider
		{
			None,
			LeftTrigger,
			RightTrigger,
			LeftThumbX,
			LeftThumbY,
			RightThumbX,
			RightThumbY
		};

		struct Binding
		{
			Binding() = default;
			Binding(uint32_t buttons) : BoundButtons{ buttons }
			{
			}
			Binding(Button button) : BoundButtons{ static_cast<uint32_t>(button) }
			{
			}
			// optional required button to be pressed with value provider (Combo: LeftThumbX + X)
			Binding(ValueProvider provider, Button button = Button::None) : BoundProvider{ provider }, BoundButtons{ static_cast<uint32_t>(button) }
			{
			}
			// needs a value provider having a value and multiple buttons pressed at the same time (Combo: LeftThumbX + X + A)
			Binding(ValueProvider provider, uint32_t buttons) : BoundProvider{ provider }, BoundButtons{ buttons }
			{
			}

			uint32_t	   BoundButtons{ 0 };
			ValueProvider  BoundProvider{ ValueProvider::None };
		};

		Gamepad();
		~Gamepad();

		Gamepad(const Gamepad&) = delete;
		Gamepad(Gamepad&&) noexcept = delete;
		Gamepad& operator=(const Gamepad&) = delete;
		Gamepad& operator=(Gamepad&&) noexcept = delete;

		uint32_t GetDeviceIndex() const;
		uint32_t GetPlayerIndex() const;
		void AssignToPlayer(uint32_t index);

		bool IsConnected() const { return m_IsConnected; }

#ifdef _DEBUG
		glm::vec2 DEBUG_GetLeftThumbInput();
#endif

		void SetDeadzone(float deadzone);
		float GetDeadzone();

		void* GetCurrentState();
		void* GetPreviousState();

		void SetConnectionResult(bool result) { m_IsConnected = result; }

	protected:
		Gamepad(bool ignoreImplementationPtr);

	private:
		class GamepadImplementation;
		std::unique_ptr<GamepadImplementation> m_ImplementationPtr{};

		bool m_IsConnected{ false };
	};

	uint32_t operator|(Gamepad::Button left, Gamepad::Button right);
}
