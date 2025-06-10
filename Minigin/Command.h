#pragma once
#include "Singleton.h"
#include "Keybind.h"
#include <any>

namespace dae
{
	class GameObject;
	class InputAction;
	class Command
	{
	public:
		virtual ~Command() = 0 {}

		virtual void Execute(float deltaTime) = 0;

	protected:
		Command() = default;

	private:

	};

	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand() = delete;
		virtual ~GameObjectCommand() = 0 {}

		virtual void Execute(float deltaTime) = 0;

		GameObject* GetGameObject() { return m_GameObjectPtr; }

	protected:
		GameObjectCommand(GameObject* gameObject) : m_GameObjectPtr{ gameObject }
		{
		}

	private:
		GameObject* m_GameObjectPtr;
	};
}