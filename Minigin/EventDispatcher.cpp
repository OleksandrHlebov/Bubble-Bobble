#include "EventDispatcher.h"
#include "GameEvent.h"

void dae::EventDispatcher::HandleDispatchedEvents()
{
	m_BlockDispatcher = true;
	while (!m_EventsToDispatch.empty())
	{
		GameEvent* currentEvent{ m_EventsToDispatch.front().get() };
		const std::vector<EventHandler>& handlersToCall = m_BoundHandlers[currentEvent->ID];
		for (const auto& handler : handlersToCall)
			handler(currentEvent);
		m_EventsToDispatch.pop();
	}
	m_BlockDispatcher = false;
}

dae::EventDispatcher::EventDispatcher()
{
}

dae::EventDispatcher::~EventDispatcher()
{
}
