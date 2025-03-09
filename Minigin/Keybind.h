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
		Keybind(Gamepad::ValueProvider provider) : GamepadBinding{ provider }
		{
		}
		Keybind(SDL_Scancode scancode) : KeyboardBinding{ scancode }
		{
		}

		Gamepad::Binding GamepadBinding{};
		SDL_Scancode	 KeyboardBinding{ SDL_SCANCODE_UNKNOWN };
	};

}