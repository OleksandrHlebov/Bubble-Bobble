#pragma once
#include "Singleton.h"
#include "Keybind.h"
#include <any>

namespace dae
{
	class GameObject;
	class Command
	{
	public:
		virtual ~Command() = 0 {}

		virtual void Execute(GameObject* object, float value, float deltaTime) = 0;

	protected:
		Command() = default;

	private:

	};
}