#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	class UIValueTweaker : public Component
	{
	public:
		UIValueTweaker() = delete;
		UIValueTweaker(GameObject* owner) : Component(owner) {}
		~UIValueTweaker() = default;
		
		UIValueTweaker(const UIValueTweaker&) 					= delete;
		UIValueTweaker(UIValueTweaker&&) noexcept 				= delete;
		UIValueTweaker& operator=(const UIValueTweaker&) 	 	= delete;
		UIValueTweaker& operator=(UIValueTweaker&&) noexcept 	= delete;

		void AddPlayer(GameObject* player);

		void RenderUI() override;

	private:
		std::vector<GameObject*> m_Players;
	};
}