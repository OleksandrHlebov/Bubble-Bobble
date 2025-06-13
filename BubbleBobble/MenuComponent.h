#pragma once
#include "Component.h"
#include "Font.h"
#include <vector>
#include <functional>
#include <memory>
#include "SDL_pixels.h"
#include <glm.hpp>

namespace dae
{
	class MenuComponent final : public Component
	{
	public:
		MenuComponent() = delete;
		MenuComponent(std::shared_ptr<Font> font, bool isHorizontal, GameObject* owner)
			: Component(owner)
			, m_IsHorizontal{ isHorizontal }
			, m_Font{ font }
			{}
		MenuComponent(std::shared_ptr<Font> font, GameObject* owner)
			: MenuComponent(font, false, owner)
			{}
		~MenuComponent() = default;
		
		MenuComponent(const MenuComponent&) 				= delete;
		MenuComponent(MenuComponent&&) noexcept 			= delete;
		MenuComponent& operator=(const MenuComponent&) 	 	= delete;
		MenuComponent& operator=(MenuComponent&&) noexcept 	= delete;

		void AddButton(const std::string& label, std::function<void(const glm::ivec2&)> inputHandler);

		void ProcessInput(const glm::ivec3& input);

	private:
		const float m_Margin{ 12.f };
		std::vector<std::function<void(const glm::ivec2&)>> m_Delegates;
		std::vector<GameObject*> m_ButtonObjects;
		std::shared_ptr<Font> m_Font;

		SDL_Color m_SelectedColor{ 255, 255, 255, 255 };
		SDL_Color m_InActiveColor{ 177, 177, 223, 255 };

		int m_SelectedIndex{};
		bool m_IsHorizontal;
	};
}