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

		static void Bind(const std::string& id, EventHandler* handler)
		{
			EventDispatcher::GetInstance().Bind(id, handler);
		}

		static void UnBind(const std::string& id, EventHandler* handler)
		{
			EventDispatcher::GetInstance().UnBind(id, handler);
		}

		virtual bool AllowedLayeredDispatch() const { return m_AllowedDispatchFromOtherEvents; }

		const std::string ID;

	protected:
		GameEvent() = delete;
		// allow dispatch from other events at your own risk, may result in infinite loop
		constexpr explicit GameEvent(const std::string& id, bool allowDispatchFromOtherEvents = false) : ID{ id }, m_AllowedDispatchFromOtherEvents{ allowDispatchFromOtherEvents }
		{
		}
	private:
		const bool m_AllowedDispatchFromOtherEvents;
	};
}