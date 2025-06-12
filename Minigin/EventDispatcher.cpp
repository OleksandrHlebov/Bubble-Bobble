#include "EventDispatcher.h"
#include "GameEvent.h"

void dae::EventDispatcher::HandleDispatchedEvents()
{
	m_BlockDispatcher = true;
	int eventsHandledThisFrame{ 0 };
	while (!m_EventsToDispatch.empty() && eventsHandledThisFrame < MAX_EVENTS_PER_FRAME)
	{
		GameEvent* currentEvent{ m_EventsToDispatch.front().get() };
		std::vector<EventHandler*>& handlersToCall = m_BoundHandlers[currentEvent->ID];
		for (EventHandler* handler : handlersToCall)
			if (std::find(m_HandlersToUnbind.begin(), m_HandlersToUnbind.end()
				, std::make_pair(currentEvent->ID, handler)) == m_HandlersToUnbind.end())
				(*handler)(currentEvent);
		m_EventsToDispatch.pop();
		++eventsHandledThisFrame;
	}
	while (!m_HandlersToUnbind.empty())
	{
		auto [id, handler] = m_HandlersToUnbind.back();
		m_HandlersToUnbind.pop_back();
		UnBind_Impl(id, handler);
	}
	m_BlockDispatcher = false;
}

dae::EventDispatcher::EventDispatcher()
{
}

dae::EventDispatcher::~EventDispatcher()
{
}
