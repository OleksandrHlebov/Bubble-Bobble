#pragma once
#include "SDL_scancode.h"
#include <vector>
#include "Gamepad.h"

namespace dae
{
	struct Keybind
	{
		Keybind() = default;
		Keybind(uint32_t gamepadButtons) : GamepadBinding{ gamepadButtons }
		{
		}
		Keybind(Gamepad::Button gamepadButton) : GamepadBinding{ gamepadButton }
		{
		}
		Keybind(Gamepad::ValueProvider provider, Gamepad::Button button = Gamepad::Button::None) : GamepadBinding{ provider, button }
		{
		}
		Keybind(Gamepad::ValueProvider provider, uint32_t buttons) : GamepadBinding{ provider, buttons }
		{
		}
		Keybind(SDL_Scancode scancode) : KeyboardBinding{ scancode }
		{
		}

		Gamepad::Binding GamepadBinding{};
		SDL_Scancode	 KeyboardBinding{ SDL_SCANCODE_UNKNOWN };
	};

}