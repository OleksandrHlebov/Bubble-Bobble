#pragma once
#include "Singleton.h"

namespace dae
{
	class GameObject;
	class Command
	{
	public:
		virtual ~Command() = 0 {}

		virtual void Execute(GameObject* object, float deltaTime) = 0;

	protected:
		Command() = default;

	private:

	};
}