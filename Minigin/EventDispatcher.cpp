#include "EventDispatcher.h"
#include "GameEvent.h"

void dae::EventDispatcher::HandleDispatchedEvents()
{
	m_BlockDispatcher = true;
	int eventsHandledThisFrame{ 0 };
	while (!m_EventsToDispatch.empty() && eventsHandledThisFrame < MAX_EVENTS_PER_FRAME)
	{
		GameEvent* currentEvent{ m_EventsToDispatch.front().get() };
		const std::vector<EventHandler>& handlersToCall = m_BoundHandlers[currentEvent->ID];
		for (const auto& handler : handlersToCall)
			handler(currentEvent);
		m_EventsToDispatch.pop();
		++eventsHandledThisFrame;
	}
	m_BlockDispatcher = false;
}

dae::EventDispatcher::EventDispatcher()
{
}

dae::EventDispatcher::~EventDispatcher()
{
}
