#pragma once
#include "Singleton.h"
#include <queue>
#include <unordered_map>
#include <string>
#include <memory>
#include <functional>
#include <utility>
#include <vector>
#include <cassert>
#include <exception>
#include <typeinfo>

namespace dae
{
	struct GameEvent;
	using EventHandler = std::function<void(GameEvent*)>;
	class EventDispatcher final : public Singleton<EventDispatcher>
	{
	public:
		EventDispatcher();
		~EventDispatcher();


		class bad_dispatch final : public std::exception
		{
		public:
			const char* what() const throw()
			{
				return "Dispatching event from event handler";
			}
		};

		template<typename GameEventType, typename... Args>
		void Dispatch(Args&&... eventArguments)
		{
			// Game programming patterns suggested rule
			// to avoid cycles: https://shorturl.at/KgyfA
			if (m_BlockDispatcher)
				throw bad_dispatch();
			m_EventsToDispatch.push(std::make_unique<GameEventType>(eventArguments...));
		}

		void Bind(const std::string& id, const EventHandler& handler)
		{
			m_BoundHandlers[id].emplace_back(handler);
		}

		void HandleDispatchedEvents();

	private:
		friend struct GameEvent;

		bool m_BlockDispatcher{ false };
		std::unordered_map<std::string, std::vector<EventHandler>> m_BoundHandlers;
		std::queue<std::unique_ptr<GameEvent>> m_EventsToDispatch;
	};
}