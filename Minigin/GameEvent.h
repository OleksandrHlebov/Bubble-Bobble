#pragma once
#include "EventDispatcher.h"

namespace dae
{
	struct GameEvent
	{
		virtual ~GameEvent() = default;

		template<typename GameEventType, typename... Args>
		static void Dispatch(Args&&... constructorArguments)
		{
			EventDispatcher::GetInstance().Dispatch<GameEventType>(constructorArguments...);
		}

		static void Bind(const std::string& id, const EventHandler& handler)
		{
			EventDispatcher::GetInstance().Bind(id, handler);
		}

		static void UnBind(const std::string& id, const EventHandler& handler)
		{
			EventDispatcher::GetInstance().UnBind(id, handler);
		}

		const std::string ID;

	protected:
		GameEvent() = delete;
		constexpr explicit GameEvent(const std::string& id) : ID{ id }
		{
		}
	};
}