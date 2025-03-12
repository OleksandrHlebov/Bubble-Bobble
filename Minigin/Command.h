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

		virtual void Execute() = 0;

		void Initialize(InputAction* inputAction) { m_InputAction = inputAction; }

	protected:
		Command() = default;
		Command(InputAction* inputAction) : m_InputAction{ inputAction }
		{
		}
		InputAction* GetInputAction() { return m_InputAction; }

	private:
		InputAction* m_InputAction;
	};

	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand() = delete;
		virtual ~GameObjectCommand() = 0 {}

		virtual void Execute() = 0;

		GameObject* GetGameObject() { return m_GameObjectPtr; }

	protected:
		GameObjectCommand(GameObject* gameObject) : m_GameObjectPtr{ gameObject }
		{
		}

	private:
		GameObject* m_GameObjectPtr;
	};
}