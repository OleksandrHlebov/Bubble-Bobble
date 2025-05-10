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
			std::unique_ptr<GameEventType> event = std::make_unique<GameEventType>(eventArguments...);
			// Game programming patterns suggested rule
			// to avoid cycles: https://shorturl.at/KgyfA
			if (m_BlockDispatcher)
			{
				std::cout << "Event " << event->ID << " dispatched, while event " << m_EventsToDispatch.front().get()->ID << " was being processed\n";
				throw bad_dispatch();
			}
			m_EventsToDispatch.push(std::move(event));
		}

		void Bind(const std::string& id, const EventHandler& handler)
		{
			m_BoundHandlers[id].emplace_back(handler);
		}

		void UnBind(const std::string& id, const EventHandler& handler)
		{
			std::erase_if(m_BoundHandlers[id], [&handler](EventHandler& boundHandler) 
				{
					// https://stackoverflow.com/questions/18039723/c-trying-to-get-function-address-from-a-stdfunction
					auto name1 = *(long*)(char*)(&handler);
					auto name2 = *(long*)(char*)(&boundHandler);
					return name1 == name2;
				});
		}

		void HandleDispatchedEvents();

	private:
		inline static const int MAX_EVENTS_PER_FRAME{ 16 };

		bool m_BlockDispatcher{ false };
		std::unordered_map<std::string, std::vector<EventHandler>> m_BoundHandlers;
		std::queue<std::unique_ptr<GameEvent>> m_EventsToDispatch;
	};
}