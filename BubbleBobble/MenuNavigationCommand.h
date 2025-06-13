#pragma once
#include "Command.h"
#include "MenuComponent.h"

namespace dae
{
	class MenuNavigationCommand final : public GameObjectCommand
	{
	public:
		MenuNavigationCommand() = delete;
		MenuNavigationCommand(GameObject* gameObject, const glm::ivec3& input)
			: GameObjectCommand(gameObject)
			, m_Input{ input }
			{}
		~MenuNavigationCommand() = default;
		
		MenuNavigationCommand(const MenuNavigationCommand&) 				= delete;
		MenuNavigationCommand(MenuNavigationCommand&&) noexcept 			= delete;
		MenuNavigationCommand& operator=(const MenuNavigationCommand&) 	 	= delete;
		MenuNavigationCommand& operator=(MenuNavigationCommand&&) noexcept 	= delete;

		void Execute(float deltaTime) override
		{
			auto menu = (GetGameObject()->GetComponent<MenuComponent>());
			if (menu)
				menu->ProcessInput(input);
		}

	private:
		glm::ivec3 m_Input;
	};
}
