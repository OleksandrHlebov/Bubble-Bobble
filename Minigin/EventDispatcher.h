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
#include <iostream>
#include "Command.h"

namespace dae
{
	struct GameEvent;

	class EventHandler
	{
	public:
		EventHandler(std::function<void(GameEvent*)> func) : m_Func{ func } {}
		void operator()(GameEvent* event)
		{
			m_Func(event);
		}
	private:
		std::function<void(GameEvent*)> m_Func;
	};

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
			std::unique_ptr<GameEventType> event = std::make_unique<GameEventType>(eventArguments...);
			// Game programming patterns suggested rule
			// to avoid cycles
			if (m_BlockDispatcher && !event->AllowedLayeredDispatch())
			{
				std::cout << "Event " << event->ID << " dispatched, while event " << m_EventsToDispatch.front().get()->ID << " was being processed\n";
				throw bad_dispatch();
			}
			m_EventsToDispatch.push(std::move(event));
		}

		void UnBind(const std::string& id, EventHandler* handler)
		{
			m_HandlersToUnbind.emplace_back(id, handler);
		}

		void Bind(const std::string& id, EventHandler* handler)
		{
			m_BoundHandlers[id].emplace_back(handler);
		}

		void Clear() { m_BoundHandlers.clear(); m_EventsToDispatch = {}; }

		void HandleDispatchedEvents();

	private:
		void UnBind_Impl(const std::string& id, EventHandler* handler)
		{
			std::erase(m_BoundHandlers[id], handler);
		}
		inline static const int MAX_EVENTS_PER_FRAME{ 256 };

		bool m_BlockDispatcher{ false };
		std::unordered_map<std::string, std::vector<EventHandler*>> m_BoundHandlers;
		std::queue<std::unique_ptr<GameEvent>> m_EventsToDispatch;
		std::vector<std::pair<std::string, EventHandler*>> m_HandlersToUnbind;
	};
}