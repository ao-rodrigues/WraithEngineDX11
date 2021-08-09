#include "wrpch.h"
#include "EventBus.h"

namespace Wraith
{
	std::unordered_map<size_t, std::vector<EventCallback<Event>>> EventBus::s_listeners;
}
